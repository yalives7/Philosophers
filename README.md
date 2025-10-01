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


