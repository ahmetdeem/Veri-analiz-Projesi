# veri_analiz_projesi

C ile kişisel veri analizi uygulaması

Bu proje, C programlama dili ile hazırlanmış bir kişisel harcama analiz programıdır. Uygulama, data.txt dosyasındaki gelir–gider kayıtlarını okuyarak kullanıcıya çeşitli analizler sunar.

Özellikler

Tüm veriyi listeleme

Toplam harcama ve günlük ortalama gider hesaplama

En az ve en çok harcama yapılan gün analizi

Eşik değer analiz ekranı

Tarih aralığına göre filtreleme

Belirli tutarın üzerindeki harcamaları listeleme

Gelecek ay tahmini gider hesaplama

Kullanım

Programı derlemek için:

gcc veri_analiz_asistani.c -o analiz


Çalıştırmak için:

./analiz


Programın doğru çalışması için data.txt dosyasıyla aynı klasörde bulunmalıdır.

Veri Seti Formatı
tarih tur kategori aciklama miktar birimfiyat toplamtutar odemesekli
2025-11-01 Gider Tekel Sigara 1 100 100 Nakit

Menü
1 - Tüm veriyi listele
2 - Toplam ve günlük ortalama harcamayı göster
3 - En az / en çok harcama yapılan günü göster
4 - Eşik değer analizini yap
5 - Gelecek ay ortalama gider tahmini
0 - Çıkış

Proje Amacı

Bu proje, C dilinde dosya okuma, string işlemleri, dizi yönetimi, fonksiyon yapıları ve kullanıcı etkileşimi konularında pratik yapmak amacıyla geliştirilmiştir. Gerçek hayattan alınmış harcama verileri kullanılarak temel finansal analizlerin yapılabilmesi hedeflenmiştir.
