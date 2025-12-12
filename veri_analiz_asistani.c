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
                printf("a \n");
                break;
                /* Toplama ve günlük ortalama harcamayı göster  */
            case 2:
                printf("b \n");
                break;
                /* en az ve en çok harcama yapılan günü göster  */
            case 3:
                printf("c \n");
                break;
                /* eşik değer analizi */
            case 4:
                printf("d \n");
                break;
                /* Gelecek ay gider tahmini */
            case 5:
                printf("e \n");
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
