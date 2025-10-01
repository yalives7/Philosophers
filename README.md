# Dining Philosophers Problem 🍝

## 🎯 Giriş
42'nin **philosophers** projesine ilham veren bu problem, çoklu süreçler (process) veya iş parçacıkları (thread) arasındaki **senkronizasyon** ve **kaynak paylaşımı** sorunlarını öğretmek için kurgulanmıştır. Temel amaç; deadlock, race condition ve starvation gibi problemleri örnekleyip, bu durumların nasıl önleneceğini göstermektir.

## 📜 Tarihçe
Dining Philosophers (Yemek Yiyen Filozoflar) problemi ilk olarak **1965'te Edsger W. Dijkstra** tarafından tanımlanmıştır. Daha sonra **Tony Hoare** gibi bilgisayar bilimcileri tarafından popülerleştirilmiş ve işletim sistemleri / concurrency derslerinin klasik örneklerinden biri haline gelmiştir.

## ❓ Problem Nedir?
- Bir masada **N filozof** yuvarlak şekilde oturur.
- Her filozofun önünde bir tabak yemek vardır ve **yemek yemek için iki çatal** gerekir (sağ ve sol).
- Filozoflar sırayla **düşünür**, **yemek yer** veya **dinlenir**.
- Eğer çatallar uygun şekilde paylaşılmazsa sistemde çeşitli sorunlar ortaya çıkar: **deadlock**, **race condition**, **starvation**.

## ⚠️ Karşılaşılan Problemler

### 🛑 Deadlock (Kilitlenme)
- Tanım: Bir grup işlem birbirinin serbest bırakacağı kaynağı bekler ve hiçbiri ilerleyemez.
- Neden önlenmeli: Sistem veya program belirli bir noktada takılır; kaynaklar boşuna tutulur ve ilerleme durur.
- Örnek: Her filozof önce sol çatalı alıp sağ çatalı beklerse, herkes tek çatalda sıkışır ve kimse yemek yiyemez.

### 🔄 Race Condition (Yarış Durumu)
- Tanım: Birden fazla işlem aynı veriyi eşzamanlı ve kontrolsüz şekilde okur/yazar; sonuçlar belirsiz olur.
- Neden önlenmeli: Veri tutarsızlığı (data corruption), beklenmedik davranışlar ve hata oluşur.
- Somut örnek:
  - İki filozof aynı anda `yemek_sayisi` değişkenini güncelliyor.
  - Filozof A eski değeri okur, +1 yapar; aynı anda filozof B de eski değeri okuyup +1 yapar.
  - Beklenen artış `+2` iken kaydedilen `+1` olur — yapılan değişikliklerden biri üzerine yazılmıştır.

### 🍽️ Starvation (Aç Kalma)
- Tanım: Bazı işlemler sürekli kaynak bulurken bazıları hiç kaynak bulamaz; adil olmayan paylaşım.
- Neden önlenmeli: Sistemde bazı işlevler veya kullanıcılar sürekli ihmal edilir; canlılık (liveness) ve adalet bozulur.
- Örnek: Hızlı veya öncelikli filozoflar sürekli çatalları kapar; yavaş filozof hiçbir zaman yemek yiyemez.

## 🧵 Thread ve Fork Kavramları

### **Thread Nedir?**
- **Thread (İş Parçacığı):** Aynı program içinde eşzamanlı çalışan bağımsız kod blokları
- **Main Thread:** `int main()` fonksiyonunun çalıştığı ana thread - tüm diğer thread'leri yönetir
- **Bu projede:** Her filozof ayrı bir thread'de çalışır, böylece aynı anda düşünüp yemek yiyebilirler

### **Fork vs Thread Farkı**
- **Fork:** Tamamen ayrı process oluşturur (bellekleri ayrı)
- **Thread:** Aynı belleği paylaşan hafif işlemler
- **Neden Thread:** Çatallar (forks) gibi paylaşılan kaynaklar olduğu için thread kullandık

##  Program Nasıl Çalışır?

### 📋 Kullanım
```bash
./philo <filozofar> <ölme_süresi> <yeme_süresi> <uyku_süresi> [min_yemek]

# Örnek:
./philo 5 800 200 200 3
# 5 filozof, 800ms'de ölür, 200ms yer, 200ms uyur, 3 kez yemeli
```

### � Ana Thread Yönetimi (Main Thread)

**`int main()` - Program Başlangıcı:**
```c
int main(int ac, char **av)
{
    t_data data;
    
    parse_args(ac, av, &data);        // Argümanları çözümle
    init_all(&data);                  // Tüm kaynakları hazırla
    start_simulation(&data);          // Thread'leri başlat ve bekle
    clean_up(&data);                  // Temizlik yap
    return (0);
}
```

**Ana Thread'in Görevleri:**
1. **Kaynak Yönetimi:** Bellek ayırma, mutex'leri kurup temizleme
2. **Thread Management:** Filozof thread'lerini başlatma ve bekleme
3. **Koordinasyon:** Tüm işlem bitince temizlik yapma

### 🔄 Thread Yapısı

```c
void start_simulation(t_data *data)
{
    pthread_t monitor;
    
    // 1. Ölüm kontrol thread'i başlat
    pthread_create(&monitor, NULL, monitor_routine, data);
    
    // 2. Her filozof için thread oluştur
    for (int i = 0; i < data->num_philos; i++)
        pthread_create(&data->philos[i].thread, NULL, philosopher_routine, &data->philos[i]);
    
    // 3. Ana thread burada bekler (join)
    for (int i = 0; i < data->num_philos; i++)
        pthread_join(data->philos[i].thread, NULL);
    
    pthread_join(monitor, NULL);
}
```

### 👨‍🍳 Filozof Yaşam Döngüsü

**Her Filozof Thread'i:**
1. **Think** (Düşün) → 2. **Grab Forks** (Çatal Al) → 3. **Eat** (Ye) → 4. **Sleep** (Uyu) → Tekrar

```c
void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    while (!simulation_ended)
    {
        grab_forks(philo);     // Mutex ile çatal al
        eat(philo);            // Yemek ye (zaman güncelle)
        release_forks(philo);  // Mutex'leri serbest bırak
        sleep_philo(philo);    // Belirtilen süre uyu
        think(philo);          // Düşün
    }
}
```

### 👁️ Monitor Thread

**Sürekli kontrol eden ayrı thread:**
- Her filozofun son yemek zamanını kontrol eder
- Biri ölürse simülasyonu durdurur
- Hepsi yeterince yemek yediyse bitirir

### 📊 Test Örnekleri

```bash
# Temel test - kimse ölmemeli
./philo 4 800 200 200

# Zorlu test - ölüm olabilir
./philo 4 310 200 100

# Tek filozof - kesinlikle ölür
./philo 1 800 200 200
```

Bu yapı sayesinde **main thread** tüm işlemi kontrol ederken, her filozof bağımsız çalışır ve kaynaklar güvenli paylaşılır! 🎉

## 🛡️ Problemlerin Çözümü

### 🔒 **Deadlock Nasıl Önlendi?**
**Problem:** Herkes aynı anda sol çatalı alırsa, sağ çatal için sonsuza kadar beklerler.

**Çözüm - Asimetrik Çatal Alma:**
```c
// Çift numaralı filozoflar ters sırada alır
if (philo->id % 2 == 0) {
    first_fork = philo->right_fork;  // Önce sağ
    second_fork = philo->left_fork;  // Sonra sol
}
```
Böylece döngüsel bekleme kırılır!

### 🔄 **Data Race Nasıl Önlendi?**
**Problem:** İki thread aynı veriyi aynı anda değiştirirse karışıklık olur.

**Çözüm - Mutex Kilitleri:**
```c
// Yazdırma işlemi için
safe_mutex_lock(&data->print_mutex);
printf("%lld %d is eating\n", time, philo_id);
safe_mutex_unlock(&data->print_mutex);

// Ölüm kontrolü için  
safe_mutex_lock(&data->death_mutex);
philo->last_meal = current_time;
safe_mutex_unlock(&data->death_mutex);
```
**Sonuç:** Aynı anda sadece bir thread kritik bölüme girebilir.


