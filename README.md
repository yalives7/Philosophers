Dining Philosophers Problem 🍝

📜 Tarihçe

Dining Philosophers (Yemek Yiyen Filozoflar) problemi ilk kez 1965’te Edsger W. Dijkstra tarafından ortaya atıldı.
Amaç, çoklu süreçler (process) veya iş parçacıkları (thread) aynı anda ortak kaynakları paylaşırken ortaya çıkabilecek senkronizasyon sorunlarını göstermekti.
Daha sonra Tony Hoare bu problemi popülerleştirdi ve işletim sistemleri derslerinde klasik bir örnek haline geldi.

❓ Problem Nedir?

Bir masada N filozof yuvarlak şekilde oturur. Her filozofun önünde bir tabak yemek vardır ve yemek yiyebilmek için iki çatal gerekir.

Filozoflar şu üç eylemi yapabilir:

💭 Düşünmek

🍝 Yemek yemek

😴 Uyumak 

Her filozofun sağında ve solunda birer çatal vardır.

Sorun şuradan doğar:

Eğer tüm filozoflar aynı anda yemek için çatalları almaya kalkarsa → Deadlock oluşur.

Eğer bazı filozoflar sürekli yemek yeme fırsatı bulurken bazıları hiç bulamazsa → Starvation ortaya çıkar.

Eğer aynı anda iki filozof aynı kaynağa (örneğin aynı çatal) erişmeye çalışırsa → Race Condition yaşanır.


⚠️ Karşılaşılan Problemler

🛑 Deadlock (Kilitlenme)

Tüm süreçler birbirini bekler, hiçbir işlem ilerleyemez.
📌 Örnek: Her filozof solundaki çatalı alıp sağındakini beklerse herkes sonsuza kadar aç kalır.

🔄 Race Condition (Yarış Durumu)

Birden fazla süreç aynı anda aynı kaynağa kontrolsüz şekilde erişmeye çalışırsa beklenmedik sonuçlar oluşur.

📌 Örnek senaryo:

İki filozof aynı anda “yemeğe başladım” bilgisini güncellemek için aynı değişkene erişiyor.

Biri değişkeni +1 yapıyor ama tam o sırada diğeri eski değeri okuyup +1 yapıyor.

Sonuçta beklenen değer +2 olması gerekirken yalnızca +1 kaydediliyor.

👉 Yani biri yaptığı değişikliği diğeri fark etmeden üzerine yazıyor → bu yüzden veri bozulması (data corruption) olur.

🍽️ Starvation (Aç Kalma)

Bazı süreçler sürekli kaynak bulurken diğerleri hiç kaynak bulamaz.
📌 Örnek: Hızlı olan filozof hep çatalları kapar, yavaş olan hiçbir zaman yemek yiyemez.

Bu yüzden adil kaynak paylaşımı sağlamak gerekir.
