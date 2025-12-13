#include <stdbool.h>
#include <stdio.h>
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

    //Toplamve günlük ortalama fonksiyonu tanımı menü 2. seçenek
    void ToplamVeGunlukOrtalama();

    //gün bazlı min max fonksiyonu tanımı menü 3. seçenek
    void GunBazliMinMax();

    // eşik değer analizi fonksiyonu menü 4. seçenek
    void EsikDegerAnalizi();

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
              //ToplamVeGunlukOrtalama();
                break;
                /* en az ve en çok harcama yapılan günü göster  */
            case 3:
            //  GunBazliMinMax();
                break;
                /* eşik değer analizi */
            case 4:
           //  EsikDegerAnalizi();
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
