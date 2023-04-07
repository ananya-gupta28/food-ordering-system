#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int total = 0;
char *line;
char *readline(FILE *file)
{
    char *ln;
    ln = (char *)calloc(1, sizeof(char));
    char chr = ' ';
    fscanf(file, "%c", &chr);
    int i = 0;
    while (chr != '\n' && chr != EOF)
    {
        ln[i] = chr;
        fscanf(file, "%c", &chr);
        if (chr != '\n')
        {
            i++;
            ln = (char *)realloc(ln, (i + 1) * sizeof(char));
            if (ln == NULL)
            {
                printf("error");
            }
        }
        else
        {
            i++;
            ln = (char *)realloc(ln, (i + 1) * sizeof(char));
            ln[i] = '\0';
        }
    }
    int l = strlen(ln);
    return ln;
}
int fetch_restaurant(char **rest_list)
{
    printf("\n\nHello , Meal time\n\nSelect your restaurant\n\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d. %s\n\n", i + 1, rest_list[i]);
    }
    printf("Enter * to exit\n\n");
    int restaurant_key = 0;
    {
        char c;
        do
        {
            c = getchar();
            if (c != '\n')
            {
                if (c != '*')
                {
                    restaurant_key += c - '0';
                    restaurant_key *= 10;
                }
                else
                    restaurant_key = c;
            }
        } while (c != '\n' && c != EOF);
        if (restaurant_key != '*')
            restaurant_key /= 10;
    }
    return (restaurant_key);
}
int fetch_item()
{
    int menu_key = 0;
    {
        char c;
        do
        {
            c = getchar();
            if (c != '\n')
            {
                if (c != '*' && c != '/')
                {
                    menu_key += c - '0';
                    menu_key *= 10;
                }
                else
                    menu_key = c;
            }
        } while (c != '\n' && c != EOF);
        if (menu_key != '*' && menu_key != '/')
            menu_key /= 10;
    }
    return (menu_key);
}

void print_menu(char **menu_list, int price[], char **suffix)
{
    for (int i = 0; i < 10; i++)
    {
        printf("%d. %s %d %s\n\n", (i + 1), menu_list[i], price[i], suffix[i]);
    }
}

void get_total(int i, int price[], int amount_array[], char food[])
{
    printf("%s Selected\n\nPlease Enter an amount\n\nCurrent amount %d\n\n", food, amount_array[i - 1]);
    int amount = 0;
    {
        char c;
        do
        {
            c = getchar();
            if (c != '\n')
            {
                amount += c - '0';
                amount *= 10;
            }
        } while (c != '\n' && c != EOF);
        amount /= 10;
    }
    amount_array[i - 1] = amount;
    total = 0;
    for (int j = 0; j < 10; j++)
    {
        total += price[j] * amount_array[j];
    }
}

int main()
{
    FILE *restaurant;
    restaurant = fopen("restaurants.txt", "r");
    char **rest_list = malloc(10 * sizeof(char *));
    for (int i = 0; i < 10; i++)
    {
        line = readline(restaurant);
        rest_list[i] = malloc((strlen(line) + 1) * sizeof(char));
        for (int j = 0; j < (strlen(line)); j++)
            *(rest_list[i] + j) = *(line + j);
        *(rest_list[i] + strlen(line)) = '\0';
        free(line);
    }
    fclose(restaurant);
    while (1)
    {
        int restaurant_key = fetch_restaurant(rest_list);
        total = 0;
        FILE *menu;
        switch (restaurant_key)
        {
        case 1:
            menu = fopen("./menulist/res1.txt", "r");
            break;
        case 2:
            menu = fopen("./menulist/res2.txt", "r");
            break;
        case 3:
            menu = fopen("./menulist/res3.txt", "r");
            break;
        case 4:
            menu = fopen("./menulist/res4.txt", "r");
            break;
        case 5:
            menu = fopen("./menulist/res5.txt", "r");
            break;
        case 6:
            menu = fopen("./menulist/res6.txt", "r");
            break;
        case 7:
            menu = fopen("./menulist/res7.txt", "r");
            break;
        case 8:
            menu = fopen("./menulist/res8.txt", "r");
            break;
        case 9:
            menu = fopen("./menulist/res9.txt", "r");
            break;
        case 10:
            menu = fopen("./menulist/res10.txt", "r");
            break;
        default:
            return 0;
        }
        printf("%s\n\n", rest_list[restaurant_key - 1]);
        printf("Select an item\n\n");
        char **menu_list = malloc(10 * sizeof(char *));
        char **suffix = malloc(10 * sizeof(char *));
        ;
        int price[10];
        for (int i = 0; i < 10; i++)
        {
            line = readline(menu);
            price[i] = 0;
            // menu_list[i]=malloc((strlen(line)+1)*sizeof(char));
            int item_len = 0, suffix_len = 0;
            int suffix_start = 0;
            for (int j = 0; j < (strlen(line)); j++)
            {
                if (!((0 <= *(line + j) - '0') && (*(line + j) - '0' <= 9)))
                {
                    if (!suffix_start)
                        item_len++;
                    else
                    {
                        suffix_len++;
                    }
                }
                else
                {
                    price[i] += *(line + j) - '0';
                    price[i] *= 10;
                    suffix_start = j;
                }
            }
            price[i] /= 10;
            menu_list[i] = malloc((item_len + 1) * sizeof(char));
            suffix[i] = malloc((suffix_len + 1) * sizeof(char));
            suffix_start = 0;
            for (int j = 0, l = 0; j < (strlen(line)); j++)
            {
                if (!((0 <= *(line + j) - '0') && (*(line + j) - '0' <= 9)))
                {
                    if (!suffix_start)
                        *(menu_list[i] + j) = *(line + j);
                    else
                    {
                        *(suffix[i] + l) = *(line + j);
                        //    printf("%s\0",suffix[i]);
                        l++;
                    }
                }
                else
                {
                    suffix_start = j;
                }
            }
            *(menu_list[i] + item_len) = '\0';
            *(suffix[i] + suffix_len) = '\0';

            free(line);
        }
        fclose(menu);
        int amount_array[10];
        for (int i = 0; i < 10; i++)
            amount_array[i] = 0;
        while (1)
        {
            print_menu(menu_list, price, suffix);
            printf("Total: %d", total);
            printf("\n\nPress * to go back\n\n");
            if (total > 0)
            {
                printf("Press / to proceed to checkout\n\n");
            }
            int flag = 0, procced_to_delivery = 0;
            int menu_key = fetch_item();
            switch (menu_key)
            {
            case 1:
                system("clear");
                get_total(1, price, amount_array, menu_list[0]);
                system("clear");
                break;
            case 2:
                system("clear");
                get_total(2, price, amount_array, menu_list[1]);
                system("clear");
                break;
            case 3:
                system("clear");
                get_total(3, price, amount_array, menu_list[2]);
                system("clear");
                break;
            case 4:
                system("clear");
                get_total(4, price, amount_array, menu_list[3]);
                system("clear");
                break;
            case 5:
                system("clear");
                get_total(5, price, amount_array, menu_list[4]);
                system("clear");
                break;
            case 6:
                system("clear");
                get_total(6, price, amount_array, menu_list[5]);
                system("clear");
                break;
            case 7:
                system("clear");
                get_total(7, price, amount_array, menu_list[6]);
                system("clear");
                break;
            case 8:
                system("clear");
                get_total(8, price, amount_array, menu_list[7]);
                system("clear");
                break;
            case 9:
                system("clear");
                get_total(9, price, amount_array, menu_list[8]);
                system("clear");
                break;
            case 10:
                system("clear");
                get_total(10, price, amount_array, menu_list[9]);
                system("clear");
                break;
            case 42:
                flag = 1;
                break;
            case 47:
                printf("Press / to  proceed to confirmation\n\nPress # to go back\n\n");
                int t = getchar();
                switch (t)
                {
                case 47:
                    procced_to_delivery = 1;
                    system("clear");
                    break;
                case 35:
                    procced_to_delivery = 0;
                    system("clear");
                    break;
                default:
                    break;
                }
                break;
            default:
                printf("wrong selection , try again\n\n");
                system("clear");
            }
            if (flag)
            {
                system("clear");
                break;
            }
            if (procced_to_delivery)
            {
                printf("%s\n\nYour Total\t%d\n\nSelect a Payment method\n\n1. Pay on Delivery\n\n2. Credit Card/Debit Card\n\n3. UPI\n\nPress * to go back\n\n", rest_list[restaurant_key - 1], total);
                char c;
                int proceed = 0;
                c = getchar();
                do
                {
                    c = getchar();
                    if (c != '\n')
                    {
                        if (c != '*')
                        {
                            proceed += c - '0';
                            proceed *= 10;
                        }
                        else
                            proceed = c;
                    }
                } while (c != '\n' && c != EOF);
                if (proceed != '*')
                    proceed /= 10;

                if (proceed != '*')
                {
                    system("clear");
                    printf("Order Confirmed\n\nYour Total is %d\n\n Your meal will arrive shortly", total);
                    exit(0);
                }
                else
                {
                    continue;
                }
            }
        }
    }
}
