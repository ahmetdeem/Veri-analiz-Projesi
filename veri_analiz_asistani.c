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
        printf("Tarih Tur Kategori Aciklama Miktar BirimFiyat ToplamTutar OdemeSekli \n");
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
        printf("En az harcama yapilan gun: %s  %.2f TL\n",
               gunler[minIndex], minTutar);

        printf("En cok harcama yapilan gun: %s  %.2f TL\n",
               gunler[maxIndex], maxTutar);
    }

    // eşik değer analizi fonksiyonu menü 4. seçenek
    /*
     *TARİH KIYASLAMASI YAPABİLMEK İÇİN TARİH DEĞERİMİZİ SAYIYA ÇEVİREN BİR FONKSİYON YAZIYORUZ
     */
    int TarihiSayiyaCevir(char *tarih) {
    int y, a, g;
    //sscanf ile string mesajdan gün ay yıl değerlerini çekiyoruz
    sscanf(tarih, "%d-%d-%d", &y, &a, &g);
    return y * 10000 + a * 100 + g;
    }


    void EsikDegerAnalizi() {
        //Kullanıcıya hangi analiz türünü istediği soruyoruz
        int secim;
        printf("\nEsik Deger Analizi\n");
        printf("1 - Tarih araligindaki harcamalari listele\n");
        printf("2 - Belirli tutardan fazla harcama yapilan gunleri listele\n");
        printf("0 - Geri don\n");
        printf("Seciminiz: ");
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
            printf("Esik tutar giriniz: ");
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
            printf("\n--- %.2f TL UZERINDE YAPILAN HARCAMALAR ---\n", esik);

            for (int j = 0; j < gunSayisi; j++) {
                if (gunToplam[j] > esik) {
                    printf("%s  %.2f TL\n", gunler[j], gunToplam[j]);
                }
            }
        }
    }


    //gelecek ay tahmini fonksiyonu tanımı menü 5. seçenek
    void GelecekAyTahmini() {

            double ayToplam[13] = {0};
            int ayGunSayisi[13] = {0};   // Ay içindeki benzersiz gün sayısı
            char ayGunler[13][40][20];  // 13 ay * 40 gün * tarih stringi
            int ayGunIndex[13] = {0};   // Her ay için kaç benzersiz gün kaydedildi

            // Aylık toplam giderleri ve gün sayılarını hesaplıyoruz
            for (int i = 0; i < SatirSayisi; i++) {

                if (strcmp(DataDizisi[i].tur, "Gider") != 0)
                    continue;

                int y, a, g;
                sscanf(DataDizisi[i].tarih, "%d-%d-%d", &y, &a, &g);

                ayToplam[a] += DataDizisi[i].toplamTutar;

                // Bu gün daha önce eklenmiş mi kontrol et
                bool var = false;
                for (int k = 0; k < ayGunIndex[a]; k++) {
                    if (strcmp(ayGunler[a][k], DataDizisi[i].tarih) == 0) {
                        var = true;
                        break;
                    }
                }

                if (!var) {
                    strcpy(ayGunler[a][ayGunIndex[a]], DataDizisi[i].tarih);
                    ayGunIndex[a]++;
                }
            }

            //  Eksik ayları sonucun doğruluğunu şaşırtmaması için hesaplamaya katmıyoruz
            double toplamGider = 0;
            int tamAySayisi = 0;

            for (int ay = 1; ay <= 12; ay++) {

                if (ayGunIndex[ay] >= 25) {  // Ay içinde en az 25 farklı gün varsa tam ay kabul
                    toplamGider += ayToplam[ay];
                    tamAySayisi++;

                    printf("%d. ay (tam ay) toplam gider: %.2f TL \n",
                           ay, ayToplam[ay], ayGunIndex[ay]);
                }
                else if (ayGunIndex[ay] > 0) {
                    printf("%d. ay eksik  hesaba katilmadi \n",
                           ay, ayGunIndex[ay]);
                }
            }


            if (tamAySayisi == 0) {
                printf("\nHiç tam ay verisi yok, tahmin yapılamıyor!\n");
                return;
            }

            //  Son olarak gelecek ayın tahmini giderini hesaplayıp ekrana yazdırıyoruz
            double ortalama = toplamGider / tamAySayisi;

            printf("Gelecek ay tahmini gider: %.2f TL\n", ortalama);
        }


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
        printf("\n VERI ANALIZ ASISTANI \n");
        printf("  1 - Tum veriyi listele \n  "
                     "2 - Toplam ve gunluk ortalama harcamayi goster \n "
                     " 3 - En az / en cok harcama yapilan gunu goster \n "
                     " 4 - Esik deger analizini yap \n "
                     " 5 - Gelecek ay ortalama gider tahmini \n "
                     " 0 - Cikis \n");
        printf("Seciminiz: ");
        scanf("%d", &menusecim);
        switch (menusecim) {
            /* Tümv Veriyi Listele */
            case 1:
                TumVeriyiListele();
                printf("\n");
            break;
             /* Toplama ve günlük ortalama harcamayı göster  */
            case 2:
                ToplamVeGunlukOrtalama();
                printf("\n");
            break;
            /* en az ve en çok harcama yapılan günü göster  */
            case 3:
                GunBazliMinMax();
                printf("\n");
            break;
            /* eşik değer analizi */
            case 4:
                EsikDegerAnalizi();
                printf("\n");
            break;
             /* Gelecek ay gider tahmini */
            case 5:
                GelecekAyTahmini();
                printf("\n");
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
