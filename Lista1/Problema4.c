#include <stdio.h>

int main()
{
    float temp, conv;
    int n;
    
     while (n != 1 && n != 2)
   {
    printf("\n---------------------------Escolha uma opção (1 ou 2):-----------------------------------\n");
    printf("\n 1 - De Celsius para Fahrenheit \n 2 - De Fahrenheit para Celsius \n");
    scanf("%d", &n);
     printf("\n---------------------------------TEMPERATURA--------------------------------------------\n");
   }
    printf("\nDigite a temperatura: ");
    scanf("%f", &temp);
 printf("\n------------------------------------RESULTADO-------------------------------------------\n");
   
    switch (n)
    {
    case 1:
        conv = (temp * (9/5)) + 32;
        printf("\n %.01f C é equivalente a %.01f F \n", temp, conv );
        printf("\n----------------------------------------------------------------------------------------\n\n");
        break;

    case 2:
        conv = ((temp - 32)*5)/9;
        printf("\n %.01f F é equivalente a %.01f C \n", temp, conv);
        printf("\n----------------------------------------------------------------------------------------\n\n");
    default:
        break;
    }

    return 0;
}