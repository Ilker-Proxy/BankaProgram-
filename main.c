#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_ISLEM 100
#define KULLANICI_SAYISI 5

int aliciHesap,kullanici,i;
char yeniSifre1[20];
char yeniSifre2[20];

typedef struct {
    int hesapNo;
    char sifre[20];
    float bakiye;

} Kullanici;

void dosyadanKullaniciYukle(Kullanici kullanicilar[]) {
    FILE *dosya = fopen("musteriler.txt", "r");
    if (dosya != NULL) {
        for (i = 0; i < KULLANICI_SAYISI; i++)
            fscanf(dosya, "%d %s %f", &kullanicilar[i].hesapNo, kullanicilar[i].sifre, &kullanicilar[i].bakiye);

        fclose(dosya);
    } else
        printf("\033[0;33mKULLANICI BILGILERI DOSYASI BULUNAMADI.\n\n\n\n");

}

void kullaniciBilgileriniKaydet(Kullanici kullanicilar[]) {
    FILE *dosya = fopen("musteriler.txt", "w");
    if (dosya != NULL) {
        for (i = 0; i < KULLANICI_SAYISI; i++) {
            fprintf(dosya, "%d %s %f\n", kullanicilar[i].hesapNo, kullanicilar[i].sifre, kullanicilar[i].bakiye);
        }
        fclose(dosya);
    } else
        printf("\033[0;33mDOSYA ACILAMADI.\n");

}
void islemKaydet(const char* islem) {
    FILE *dosya = fopen("islem_gecmisi.txt", "a");
    if (dosya != NULL) {
        time_t simdikiZaman = time(NULL);
        struct tm *t = localtime(&simdikiZaman);
        fprintf(dosya, "[\033[0;35m%02d-%02d-%04d %02d:%02d:%02d] %s\n",
                t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
                t->tm_hour, t->tm_min, t->tm_sec, islem);

        fclose(dosya);
    } else
        printf("\033[0;33mDOSYA ACILAMADI.\n");

}

int main(void) {
    int kullanici, islem;
    float parayatirma, paracekme, paragonderme;
    int oturumAcik = 1;
    int denemeHakki;
    Kullanici kullanicilar[KULLANICI_SAYISI] = {
        {1001, "PASS1", 1000},
        {1002, "PASS2", 1500},
        {1003, "PASS3", 2000},
        {1004, "PASS4", 2500},
        {1005, "PASS5", 3000}
    };

    dosyadanKullaniciYukle(kullanicilar);

    while (oturumAcik) {
        printf("\033[0;33m HESAP NUMARANIZI GIRIN   : ");
        printf("\033[0;32m");
        if (scanf("%d", &kullanici) != 1) {
            printf("\033[0;33mGECERSIZ GIRIS\n");
            while (getchar() != '\n');
            continue;
        }

        Kullanici *aktifKullanici = NULL;
        for (i = 0; i < KULLANICI_SAYISI; i++) {
            if (kullanicilar[i].hesapNo == kullanici) {
                aktifKullanici = &kullanicilar[i];
                break;
            }
        }

        if (aktifKullanici == NULL) {
            printf("\033[0;33mGECERSIZ KULLANICI NUMARASI!\n");
            continue;
        }

        denemeHakki = 3;
        while (denemeHakki > 0) {
            printf("\033[0;33m");
            printf(" SIFRENIZI GIRIN: ");
            printf("\033[0;32m");
            char userPassword[20];
            scanf("%s", userPassword);

            if (strcmp(aktifKullanici->sifre, userPassword) == 0) {
                do {
                    printf("\033[0;36m");
                    printf("\n\nISLEM LISTESI\n\n\n\n");
                    printf("\033[0;31m1.\033[0;37mBAKIYE GORUNTULEME\n");
                    printf("\033[0;31m2.\033[0;37mPARA YATIRMA\n");
                    printf("\033[0;31m3.\033[0;37mPARA CEKME\n");
                    printf("\033[0;31m4.\033[0;37mPARA GONDERME\n");
                    printf("\033[0;31m5.\033[0;37mSIFRE DEGISTIRME\n");
                    printf("\033[0;31m6.\033[0;37mISLEM GECMISI GORUNTULEME\n");
                    printf("\033[0;31m7.\033[0;37mOTURUM KAPATMA\n");
                    printf("\033[0;31m8.\033[0;37mPROGRAMDAN CIKMA\n\n\n");
                    printf("SECIMINIZI YAPINIZ : ");

                    if (scanf("%d", &islem) != 1) {
                        printf("\033[0;33mGECERSIZ SECIM!\n");
                        while (getchar() != '\n');
                        continue;
                    }

                    switch (islem) {
                        case 1:
                            printf("\033[0;33m\n\nHESAP BAKIYESI: %0.2f \n", aktifKullanici->bakiye);
                            break;

                        case 2:
                            printf("\033[0;33mYATIRILACAK MIKTARI GIRIN : ");
                            if (scanf("%f", &parayatirma) == 1 && parayatirma >= 0) {
                                aktifKullanici->bakiye += parayatirma;
                                printf("\nHESAP BAKIYESI: %0.2f \n", aktifKullanici->bakiye);
                                islemKaydet("\033[0;35mPARA YATIRILDI.");
                            } else
                                printf("\033[0;33mGECERSIZ MIKTAR!\n");

                            break;

                        case 3:
                            printf("\033[0;33mCEKILECEK TUTARI GIRIN : ");
                            if (scanf("%f", &paracekme) == 1 && paracekme >= 0) {
                                if (paracekme <= aktifKullanici->bakiye) {
                                    aktifKullanici->bakiye -= paracekme;
                                    printf("\nHESAP BAKIYESI: %0.2f \n", aktifKullanici->bakiye);
                                    islemKaydet("\033[0;35mPARA CEKILDI.");
                                } else
                                    printf("\033[0;33mBAKIYE YETERSIZ.\n");

                            } else
                                printf("\033[0;33mGECERSIZ MIKTAR!\n");

                            break;
 						case 4:	printf("\033[0;33mGONDERMEK ISTEDIGINIZ HESAP NUMARASINI GIRIN : ");
    							int aliciHesap;
		    					scanf("%d", &aliciHesap);
							    if (aliciHesap == aktifKullanici->hesapNo)
							        printf("\033[0;33m\n\nKENDINIZE PARA GONDEREMEZSINIZ.\n");
							     else if (aliciHesap < 1001 || aliciHesap > 1005)

							        printf("\033[0;33mBOYLE BIR KULLANICI BULUNAMADI!\n");
							   else {

							        printf("\033[0;33mGONDERMEK ISTEDIGINIZ TUTARI GIRIN : ");
							        scanf("%f", &paragonderme);

							        if (paragonderme <= aktifKullanici->bakiye) {
							            Kullanici *alici = NULL;
					            for (i = 0; i < KULLANICI_SAYISI; i++) {
					                if (kullanicilar[i].hesapNo == aliciHesap) {
					                    alici = &kullanicilar[i];
					                    break;
					                }
					            }
					            if (alici != NULL) {
					                aktifKullanici->bakiye -= paragonderme;
					                alici->bakiye += paragonderme;
					                printf("\033[0;33mPARA GONDERILDI YENI BAKIYE %2f\n", aktifKullanici->bakiye);

					                islemKaydet("\033[0;35mPARA GONDERILDI.");
					            } else
					                printf("\033[0;33mGECERSIZ HESAP NUMARASI!\n");

					        } else
					            printf("\033[0;33m\n\nGECERSIZ MIKTAR VEYA BAKIYENIZ YETERSIZ.\n");

					    }
    							break;

                        case 5: printf("\033[0;33mMEVCUT SIFRENIZI GIRIN : ");
		                    	scanf("%s", userPassword);
		                    if (strcmp(aktifKullanici->sifre, userPassword) == 0) {
		                        printf("YENI SIFREYI GIRIN : ");
		                        scanf("%s",&yeniSifre1);
		                        printf("YENI SIFREYI TEKRAR GIRIN : ");
	                            scanf("%s",&yeniSifre2);
		                         if (strcmp(yeniSifre1, yeniSifre2) == 0) {
							        strcpy(aktifKullanici->sifre, yeniSifre1);
							        printf("SIFRENIZ BASARIYLA DEGISTIRILDI.\n");
							        kullaniciBilgileriniKaydet(kullanicilar);
							        islemKaydet("\033[0;35mSIFRENIZ DEGISTIRILDI.");
							    } else
							        printf("GIRDIGINIZ SIFRELER UYUMSUZ.\n");

							} else
							    printf("\033[0;33mMEVCUT SIFRENIZ YANLIS.\n");


		                        break;

                        case 6:
                            printf("ISLEM GECMISI:\n");
                            FILE *islemDosyasi = fopen("islem_gecmisi.txt", "r");
                            if (islemDosyasi != NULL) {
                                char line[256];
                                while (fgets(line, sizeof(line), islemDosyasi)) {
                                    printf("%s", line);
                                }
                                fclose(islemDosyasi);
                            } else
                                printf("\033[0;33mISLEM GECMISI DOSYASI ACIlMADI.\n");

                            break;

                        case 7:
                            printf("\033[0;33mOTURUM KAPATILDI.\n");
                            break;

                        case 8:
                            printf("\033[0;33m\n\nPROGRAMDAN CIKILMISTIR.\n");
                            oturumAcik = 0;
                            break;

                        default:
                            printf("\033[0;33mGECERSIZ SECIM!\n");
                            break;
                    }
                } while (islem != 7 && oturumAcik);
                break;
            } else {
                denemeHakki--;
                printf("\n\n\033[0;33mMEVCUT SIFRE YANLIS GIRILMISTIR KALAN DENEME HAKKINIZ: %d\n", denemeHakki);
            }
        }

        if (denemeHakki == 0) {
            printf("\033[0;33m3 KEZ YANLIS SIFRE GIRDINIZ.PROGRAM KAPATILIYOR.\n");
            oturumAcik = 0;
        }
    }
			printf("\033[0;37m");
    return 0;
}
