#include <stdio.h>
#include <stdlib.h>
int N,iter;

void polinomAl(float fonk[])
{
    int i;
    printf("\nPolinomun en yuksek derecesini giriniz:  ");
    scanf("%d",&N);

    for (i=N;i>=0;i--)
    {
        printf("Derecesi %d olan terimin katsayisini giriniz:  ",i);
        scanf("%f",&fonk[i]);
    }
}
float goruntu(float a,float fonk[],int n)
{
   int i=0;
   float yx=0;
   while(i<=n)
   {
          yx= yx+(fonk[i]*pow(a,i));
          i++;
   }
  return yx;
}
void turevAl(float turev[],float fonk[])
{
    int i=0;
    for(i=1;i<=N;i++){
        turev[i-1]=fonk[i]*i;
    }
}
//YONTEMLER
void grafikYontemi(float fonk[])
{
    float x,dx,e,yx,ydx,mutlak,x2;
    int ctr=0;
   printf("\nBaslangic degerini (X0) giriniz: ");
   scanf("%f",&x);
   printf("Artim degerini (delta) giriniz:   ");
   scanf("%f",&dx);
   printf("Hata payini (epsilon) giriniz:   ");
   scanf("%f",&e);
   iter=1;

   do
   {
      printf("%d.iterasyon\n",iter);
      x2=x;
      yx= goruntu(x,fonk,N);
      printf("x=%3.3f\tf(x)=%3.3f\n",x2,yx);
      do
      {

        x2=x2+dx;        //x0+delta x
        ydx= goruntu(x2,fonk,N);
        printf("x=%3.3f\tf(x)=%3.3f\n",x2,ydx);
        ctr++;
      }while((yx*ydx>0)&&(ctr<=500));
      iter++;
      x=x2-dx;
      dx=dx/2;

      mutlak=ydx-yx;
      if(mutlak<0)
         mutlak=mutlak*-1;
      printf("hata=%3.3f\n",mutlak);
   }while((e<=mutlak)&&(ctr<=500));

   if(ctr<500)
        printf("\nKok Degeri=%f",x);
   else
        printf("Bu aralikta kok yok veya girilen degerler hatali lutfen tekrar deneyiniz");
    printf("\nDevam etmek icin bir tusa basiniz...");
    getch();
}
void bisection(float fonk[])
{
    float a,b,c,e,mutlak;

    printf("Alt sinir degerini giriniz  ");
    scanf("%f",&a);
    printf("Ust sinir degerini giriniz  ");
    scanf("%f",&b);
    printf("Hata payini (epsilon) giriniz:   ");
    scanf("%f",&e);
    iter=0;
    printf("adim\t  a\t f(a)\t  b\t  f(b)\t  c\t  f(c)\n");
    do
    {
         iter++;
         c=(a+b)/2;
        printf("%3d\t%3.3f\t%3.3f\t",iter,a,goruntu(a,fonk,N));
        printf("%3.3f\t%3.3f\t",b,goruntu(b,fonk,N));
        printf("%3.3f\t%3.3f\n",c,goruntu(c,fonk,N));

        if((goruntu(c,fonk,N))==0)
        {
            printf("Kok degeri=%f",c);
            printf("\nDevam etmek icin bir tusa basiniz...");
            getch();
            return;
        }
        else
        {
            if( ( (goruntu(a,fonk,N))*(goruntu(c,fonk,N)) )<=0 )
                b=c;
            else
                a=c;
        }
        mutlak=goruntu(c,fonk,N);
        if( mutlak<0)
           mutlak=-mutlak;
    }while( (mutlak>e)&& (iter<=500));

    if(iter>=500)
        printf("Degerler hatali veya bu yontemle kok bulmak icin uygun degil");
    else
        printf("Kok degeri=%f",c);

    printf("\nDevam etmek icin bir tusa basiniz...");
    getch();
}
void RegulaFalse(float fonk[])
{

    float a,b,c,yc,e,mutlak,ceski=0;

    printf("Alt sinir degerini giriniz  ");
   scanf("%f",&a);
   printf("Ust sinir degerini giriniz  ");
   scanf("%f",&b);
    printf("Hata payini (epsilon) giriniz:   ");
    scanf("%f",&e);
    iter=0;
    printf("adim\t  a\t  b\t  c\t f(c)\n");
    do
    {
        iter++;
        c= (a*goruntu(b,fonk,N)-b*goruntu(a,fonk,N)) / (goruntu(b,fonk,N)-goruntu(a,fonk,N));

        mutlak=c-ceski;
        ceski=c;

        yc=goruntu(c,fonk,N);
        printf("%2d\t",iter);
        printf("%2.3f\t",a);
        printf("%2.3f\t ",b);
        printf("%2.3f\t%2.3f\n",c,yc);

         if (mutlak<0)
            mutlak=mutlak*-1;

        if (yc*goruntu(a,fonk,N)>=0)
            a=c;
        else
            b=c;

//    printf("mutlak=%f\n",mutlak);
//    printf("new iterasyon\n");
    }while((mutlak>e)&&(iter<=500));
    if(iter>=500)
        printf("Bu aralikta kok bulunamadi");
    else
        printf("Kok degeri=%f",a);   //a degil de c yazdiriliyor
    printf("\nDevam etmek icin bir tusa basiniz...");
    getch();
}
void NewtonRaphson(float fonk[])
{
    float mutlak,e,x;
    float turev[10];
    turevAl(turev,fonk);

   printf("Baslangic degerini giriniz  ");
   scanf("%f",&x);
    printf("Hata payini (epsilon) giriniz:   ");
   scanf("%f",&e);
   iter=0;
    do
    {
        mutlak=x- (x- (goruntu(x,fonk,N)/goruntu(x,turev,N-1)));

        x=x- (goruntu(x,fonk,N)/goruntu(x,turev,N-1));

        if(mutlak<0)
            mutlak*=-1;

    } while(mutlak>e);

    printf("Kok degeri=%3.4f",x);
    printf("\nDevam etmek icin bir tusa basiniz...");
    getch();
}
void MatInverse()
{
    float matris[10][10];
    float birim[10][10];
    int i,j,tur;
    float bolum,kat;

    printf("Matrisin satir sayisini giriniz:  ");
    scanf("%d",&N);
    for(i=0;i<=N-1;i++)
        for(j=0;j<=N-1;j++)
        {
            printf("Matrisin %d.satir %d.sutun elemanini giriniz:  ",i+1,j+1);
            scanf("%f",&matris[i][j]);
        }

    //birim matris olusturuluyor
    for(i=0;i<=N-1;i++)
        for(j=0;j<=N-1;j++)
        {
            if(i==j)
                birim[i][j]=1;
            else
                birim[i][j]=0;
        }


    for(tur=0;tur<=N-1;tur++)
    {
         bolum=matris[tur][tur];
        for(j=0;j<=N-1;j++)
        {
            matris[tur][j]=matris[tur][j]/bolum;
            birim[tur][j]/=bolum;

        }

        for(i=0;i<=N-1;i++)
        {
            if(i!=tur)
            {
                kat=matris[tur][tur]*matris[i][tur];
                for(j=0;j<=N-1;j++)
                 {
                    matris[i][j]-=matris[tur][j]*kat;
                    birim[i][j]-=birim[tur][j]*kat;
                 }
            }
        }
    }
    printf("\nGirilen Matrisin Inversi\n");
    for(i=0;i<=N-1;i++)
    {
        for(j=0;j<=N-1;j++)
            printf("%3.3f ",birim[i][j]);
        printf("\n");
    }

    printf("\nDevam etmek icin bir tusa basiniz...");
    getch();
}
void gaussJordan()
{
    float matris[10][10];
    float B[10];
    int i,j,n=3,m=3,tur;
    float bolum,kat;

     printf("Matrisin satir sayisini giriniz:  ");
     scanf("%d",&N);
     printf("*Format AX=B seklindedir*\n");
     for(i=0;i<=N-1;i++)
        for(j=0;j<=N-1;j++)
        {
            printf("A Matrisin %d.satir %d.sutun elemanini giriniz:  ",i+1,j+1);
            scanf("%f",&matris[i][j]);
        }
    for(i=0;i<=N-1;i++)
    {
        printf("B matrisinin %d.satir elemanini giriniz:  ",i+1);
        scanf("%f",&B[i]);
    }
    for(tur=0;tur<=m-1;tur++)
    {
         bolum=matris[tur][tur];
        for(j=0;j<=m-1;j++)
        {
            matris[tur][j]=matris[tur][j]/bolum;

        }
        B[tur]/=bolum;

        for(i=0;i<=n-1;i++)
        {
            if(i!=tur)
            {
                kat=matris[tur][tur]*matris[i][tur];
                for(j=0;j<=m-1;j++)
                 {
                    matris[i][j]-=matris[tur][j]*kat;
                 }
                 B[i]-=B[tur]*kat;
            }
        }
    }
    for(i=0;i<=n-1;i++)
    {
        printf("\n\tX%d=%5.2f",i+1,B[i]);
    }
    printf("\nDevam etmek icin bir tusa basiniz...");
    getch();
}
void Trapez(float dizi[])
{
    float sonuc[10];
    float a,b,h,deger,toplam=0;
    int n,i;
    printf("Alt sinir degerini giriniz  ");
    scanf("%f",&a);
    printf("Ust sinir degerini giriniz  ");
    scanf("%f",&b);
    printf("Aralik sayisini (n) giriniz:   ");
    scanf("%d",&n);

    h=(b-a)/n;
    for(i=0;i<=n;i++)
    {
        deger=a+i*h;
        sonuc[i]=goruntu(deger,dizi,N);
    }
    for(i=0;i<=n;i++)
    {
        if((i==0) || (i==n))
           toplam=toplam+sonuc[i];
        else
            toplam=toplam+2*sonuc[i];
    }

    toplam=toplam*h/2;
    printf("\ntrapez=%5.4f ",toplam);
    printf("\nDevam etmek icin bir tusa basiniz...");
    getch();
}
void Simpson(float dizi[])
{
    float sonuc[10];
    float a,b,h,deger,toplam=0;
    int n,i;

    printf("Alt sinir degerini giriniz  ");
    scanf("%f",&a);
    printf("Ust sinir degerini giriniz  ");
    scanf("%f",&b);
    printf("Aralik sayisini (n) giriniz:   ");
    scanf("%d",&n);

    h=(b-a)/n;
    for(i=0;i<=n;i++)
    {
        deger=a+i*h;
        sonuc[i]=goruntu(deger,dizi,N);
    }
   for(i=0;i<=n;i++)
    {
        if((i==0) || (i==n))
            toplam=toplam+sonuc[i];
        else if(i%2==0)
           toplam=toplam+2*sonuc[i];
        else
            toplam=toplam+4*sonuc[i];
    }

    toplam=toplam*h/3;
    printf("\nSimpson=%f\n",toplam);
    printf("\nDevam etmek icin bir tusa basiniz...");
    getch();
}
void NumericTurev(float fonk[])
{
    float h,x,turevF,turevR;
    printf("noktayi giriniz:  ");
    scanf("%f",&x);
    printf("h degerini giriniz: ");
    scanf("%f",&h);


    turevF=(goruntu(x+h,fonk,N)-goruntu(x,fonk,N))/h;
    printf("\nIleri Turev= %f",turevF);
    turevR=(goruntu(x,fonk,N)-goruntu(x-h,fonk,N))/h;
    printf("\nGeri Turev= %f",turevR);
    turevF=(turevF+turevR)/2;
    printf("\nMerkezi Turev= %f",turevF);
    printf("\nDevam etmek icin bir tusa basiniz...");
    getch();
}
int main()
{
    int input;
    float fonk[10];
    do{
        system("@cls||clear");
        printf("Kok Bulma Yontemleri\n\t1-)Grafik Yontemi\n\t2-)Yariya Bolme Yontemi\n\t3-)Regula False Yontemi\n\t"
               "4-)Newton Raphson Yontemi\nMatris Islemleri\n\t5-)Matrisin inversinin alinmasi\n\t"
               "6-)Gauss Jordan\nIntegral\n\t7-)Trapez Yontemi\n\t"
               "8-)Simpson Yontemi\nNumerik Turev\n\t9-)Ileri/Geri/Merkezi Turev\n\n");

        printf("Lutfen bir secim yapiniz (Cikmak icin -1)\n");
        scanf("%d",&input);
        system("@cls||clear");

        switch(input){

            case -1:
                break;
            case 1:
                printf("\t_Grafik Yontemi_\n");
                polinomAl(fonk);
                grafikYontemi(fonk);
                break;
            case 2:
                printf("\t_Yariya Bolme Yontemi_\n");
                polinomAl(fonk);
                bisection(fonk);
                break;
             case 3:
                printf("\t_Regula False Yontemi_\n");
                polinomAl(fonk);
                RegulaFalse(fonk);
                break;
            case 4:
                printf("\t_Newton Raphson Yontemi_\n");
                polinomAl(fonk);
                NewtonRaphson(fonk);
                break;
            case 5:
                  printf("\t_Matrisin inversinin alinmasi_\n");
                MatInverse();
                break;
            case 6:
                  printf("\t_Gauss Jordan_\n");
                  gaussJordan();
                break;
            case 7:
                printf("\t_Trapez Yontemi_\n");
                polinomAl(fonk);
                Trapez(fonk);
                break;
            case 8:
                printf("\t_Simpson Yontemi_\n");
                polinomAl(fonk);
                Simpson(fonk);
                break;
            case 9:
                  printf("\t_Ileri/Geri/Merkezi Turev_\n");
               polinomAl(fonk);
               NumericTurev(fonk);
               break;
        }

    }while(input!=-1);
    return 0;
}

