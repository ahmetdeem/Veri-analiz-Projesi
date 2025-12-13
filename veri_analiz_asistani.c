#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
 *KİŞİSEL VERİ ANALİZİ PROJESİ
 */
/*
 *STRUCT TANIMI
 */
    struct Data {
        char tarih[20];
        char tur[10];
        char kategori[20];
        char aciklama[30];
        int miktar;
        double birimFiyat;
        double toplamTutar;
        char odemeSekli[20];
    };
    struct Data DataDizisi[500];
    int SatirSayisi = 0 ;

    //Tüm Veriyi listele fonksiyonu tanımı menü 1.seçenek
    void TumVeriyiListele(){
        if(SatirSayisi == 0) {
            printf("Veri seti okunamadı");
            return;
        }
        printf("Tarih Tur Kategori Açıklama Miktar BirimFiyat ToplamTutar ÖdemeŞekli");
        for(int i = 0; i < SatirSayisi; i++) {
            printf("%s %s %s %s %d %.2f %.2f %s\n",
            DataDizisi[i].tarih,
            DataDizisi[i].tur,
            DataDizisi[i].kategori,
            DataDizisi[i].aciklama,
            DataDizisi[i].miktar,
            DataDizisi[i].birimFiyat,
            DataDizisi[i].toplamTutar,
            DataDizisi[i].odemeSekli);
        }
    }


    //Toplam ve günlük ortalama fonksiyonu tanımı menü 2. seçenek
    void ToplamVeGunlukOrtalama() {
        double toplamGider = 0 ;
        for(int i = 0; i < SatirSayisi; i++) {
            if (strcmp(DataDizisi[i].tur,"Gider") ==0) {
                toplamGider += DataDizisi[i].toplamTutar;
            }
        }
        char gunler[200][20] ;
        int gunSayisi = 0;
        bool bulundu = false;

        for (int i = 0; i < SatirSayisi; i++) {

            // tarih daha önce eklenmiş mi kontrol ediyoruz
            for (int j = 0; j < gunSayisi; j++) {
                if (strcmp(gunler[j], DataDizisi[i].tarih) == 0) {
                    bulundu = true;
                    break;
                }
            }

            // eklenmediyse yeni tarih olarak kaydediyoruz
            if (!bulundu) {
                strcpy(gunler[gunSayisi], DataDizisi[i].tarih);
                gunSayisi++;
            }

            bulundu = false;
        }
        //Günlük Ortalama gideri tanımlıyoruz burda
        double gunlukOrtalama = toplamGider / gunSayisi;

        //İstenen değerleri ekrana yazdırıyoruz
        printf("Toplam gider: %.2f TL\n", toplamGider);
        printf("Toplam gun sayisi: %d\n", gunSayisi);
        printf("Gunluk ortalama gider: %.2f TL\n", gunlukOrtalama);
        printf("\n");

    }

    //gün bazlı min max fonksiyonu tanımı menü 3. seçenek
    void GunBazliMinMax() {

        char gunler[200][20];
        double gunToplam[200];
        int gunSayisi = 0;
        //toplamları sfıra eşitliyoruz
        for (int i = 0; i < 200; i++)
            gunToplam[i] = 0;

        // TÜM SATIRLARI GEZ
        for (int i = 0; i < SatirSayisi; i++) {

            // strcmp aracılığıyla string değerleri kıyaslayıp sadece türü gider olanları işleme alıyoruz
            if (strcmp(DataDizisi[i].tur, "Gider") != 0)
                continue;

            bool bulundu = false;
            int index = -1;

            // Tarihin önceden listeye eklenip eklenmediğini kontrol ediyorum
            for (int j = 0; j < gunSayisi; j++) {
                if (strcmp(gunler[j], DataDizisi[i].tarih) == 0) {
                    bulundu = true;
                    index = j;
                    break;
                }
            }

            // Eğer tarih önceden listeye eklenmediyse ekliyorum
            if (!bulundu) {
                strcpy(gunler[gunSayisi], DataDizisi[i].tarih);
                gunToplam[gunSayisi] = DataDizisi[i].toplamTutar;
                gunSayisi++;
            }

            //tarih listede varsa eğer o tarihteki toplam gideri güncelliyorum
            else {
                gunToplam[index] += DataDizisi[i].toplamTutar;
            }
        }

        // Minimum ve maksimum değerlerine geçici olarak atama yapıyorum
        double minTutar = gunToplam[0];
        double maxTutar = gunToplam[0];
        int minIndex = 0;
        int maxIndex = 0;

        //Toplam değerleri karşılaştırıyorum
        for (int j = 1; j < gunSayisi; j++) {

            if (gunToplam[j] < minTutar) {
                minTutar = gunToplam[j];
                minIndex = j;
            }

            if (gunToplam[j] > maxTutar) {
                maxTutar = gunToplam[j];
                maxIndex = j;
            }
        }

        // döngü sonunda minIndex en küçük değerim maxIndex en büyük değerim oluyor
        printf("En az harcama yapilan gün: %s → %.2f TL\n",
               gunler[minIndex], minTutar);

        printf("En cok harcama yapilan gün: %s → %.2f TL\n",
               gunler[maxIndex], maxTutar);
    }

    // eşik değer analizi fonksiyonu menü 4. seçenek
    /*
     *TARİH KIYASLAMASI YAPABİLMEK İÇİN TARİH DEĞERİMİZİ SAYIYA ÇEVİREN BİR FONKSİYON YAZIYORUZ
     */
    int TarihiSayiyaCevir(char *tarih) {
    int y, a, g;
    sscanf(tarih, "%d-%d-%d", &y, &a, &g);
    return y * 10000 + a * 100 + g;
    }


    void EsikDegerAnalizi() {
        //Kullanıcıya hangi analiz türünü istediği soruyoruz
        int secim;
        printf("\nEşik Değer Analizi\n");
        printf("1 - Tarih aralığındaki harcamaları listele\n");
        printf("2 - Belirli tutardan fazla harcama yapılan günleri listele\n");
        printf("0 - Geri dön\n");
        printf("Seçiminiz: ");
        scanf("%d", &secim);

        // TARİH ARALIĞI ANALİZİ
        if (secim == 1) {

            char baslangic[20], bitis[20];
            printf("Baslangic tarihi (YYYY-AA-GG): ");
            scanf("%s", baslangic);
            printf("Bitis tarihi (YYYY-AA-GG): ");
            scanf("%s", bitis);

            int bas = TarihiSayiyaCevir(baslangic);
            int bit = TarihiSayiyaCevir(bitis);

            printf("\n--- Tarih Araligindaki Harcamalar ---\n");

            for (int i = 0; i < SatirSayisi; i++) {

                if (strcmp(DataDizisi[i].tur, "Gider") != 0)
                    continue;

                int t = TarihiSayiyaCevir(DataDizisi[i].tarih);

                if (t >= bas && t <= bit) {
                    printf("%s %s %s %s %d %.2f %.2f %s\n",
                           DataDizisi[i].tarih,
                           DataDizisi[i].tur,
                           DataDizisi[i].kategori,
                           DataDizisi[i].aciklama,
                           DataDizisi[i].miktar,
                           DataDizisi[i].birimFiyat,
                           DataDizisi[i].toplamTutar,
                           DataDizisi[i].odemeSekli);
                }
            }
        }

        // EŞİK TUTAR ANALİZİ
        else if (secim == 2) {

            double esik;
            printf("Eşik tutar giriniz: ");
            scanf("%lf", &esik);

            char gunler[200][20];
            double gunToplam[200];
            int gunSayisi = 0;

            for (int i = 0; i < 200; i++)
                gunToplam[i] = 0;

            // Gün bazlı toplamları hesapla
            for (int i = 0; i < SatirSayisi; i++) {

                if (strcmp(DataDizisi[i].tur, "Gider") != 0)
                    continue;

                bool bulundu = false;
                int index = -1;

                for (int j = 0; j < gunSayisi; j++) {
                    if (strcmp(gunler[j], DataDizisi[i].tarih) == 0) {
                        bulundu = true;
                        index = j;
                        break;
                    }
                }

                if (!bulundu) {
                    strcpy(gunler[gunSayisi], DataDizisi[i].tarih);
                    gunToplam[gunSayisi] = DataDizisi[i].toplamTutar;
                    gunSayisi++;
                }
                else {
                    gunToplam[index] += DataDizisi[i].toplamTutar;
                }
            }

            // EŞİĞİ GEÇEN GÜNLERİ LİSTELE
            printf("\n--- %.2f TL ÜZERİNDE HARCIYAPILAN GÜNLER ---\n", esik);

            for (int j = 0; j < gunSayisi; j++) {
                if (gunToplam[j] > esik) {
                    printf("%s → %.2f TL\n", gunler[j], gunToplam[j]);
                }
            }
        }
    }


    //gelecek ay tahmini fonksiyonu tanımı menü 5. seçenek
    void GelecekAyTahmini();

// verioku fonksiyonunu tanımlıyoruz

void verioku() {

    FILE *datadosyasi;
    char satir[200];

    datadosyasi = fopen("data.txt", "r");
    if (datadosyasi == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    // Başlık satırını atla
    fgets(satir, sizeof(satir), datadosyasi);

    // Satırları oku
    while (fscanf(datadosyasi, "%s %s %s %s %d %lf %lf %s",
                  DataDizisi[SatirSayisi].tarih,
                  DataDizisi[SatirSayisi].tur,
                  DataDizisi[SatirSayisi].kategori,
                  DataDizisi[SatirSayisi].aciklama,
                  &DataDizisi[SatirSayisi].miktar,
                  &DataDizisi[SatirSayisi].birimFiyat,
                  &DataDizisi[SatirSayisi].toplamTutar,
                  DataDizisi[SatirSayisi].odemeSekli) == 8)
    {
        SatirSayisi++;
    }

    fclose(datadosyasi);
}

int main() {


    verioku();

    int menusecim;
    bool durum=true;
    while (durum) {
        printf("1 - Tüm veriyi listele \n  "
                     "2 - Toplam ve günlük ortalama harcamayı göster \n "
                     "3 - En az / en çok harcama yapılan günü göster \n "
                     "4 - Eşik değer analizini yap \n "
                     "5 - Gelecek ay ortalama gider tahmini \n 0 - Çıkış \n");
        scanf("%d", &menusecim);
        switch (menusecim) {
            /* Tümv Veriyi Listele */
            case 1:
              TumVeriyiListele();
            break;
             /* Toplama ve günlük ortalama harcamayı göster  */
            case 2:
                ToplamVeGunlukOrtalama();
             break;
            /* en az ve en çok harcama yapılan günü göster  */
            case 3:
                GunBazliMinMax();
             break;
            /* eşik değer analizi */
            case 4:
            EsikDegerAnalizi();
             break;
             /* Gelecek ay gider tahmini */
            case 5:
            // GelecekAyTahmini();
                break;
            case 0:
                durum=false;
                break;
            default:
                printf("Belirtilen sayının karşılığı yoktur \n");

        }
    }




    getchar();
    return 0;
}
