```
#include <unistd.h>
#include <stdarg.h>

int ft_putchar(char c)
{
    return (write(1, &c, 1));
}

int ft_putnbr(int nb)
{
    int count;

    count = 0;
    if(nb == -2147483648)
    {
        count += ft_putchar('-');
        count += ft_putchar('2');
        count += ft_putnbr(147483648);
    }
    else if(nb < 0)
    {
        count += ft_putchar('-');
        count += ft_putnbr(-nb);
    }
    else if(nb >= 10)
    {
        count += ft_putnbr(nb / 10);
        count += ft_putnbr(nb % 10);
    }
    else
        count += ft_putchar(nb + '0');
    return (count);
}

int ft_putstr(char *s)
{
    int i;

    i = 0;
    if(!s)
        return (write(1, "(null)", 6));
    while(s[i] != '\0')
    {
        write(1, &s[i], 1);
        i++;
    }
    return (i);
}

int ft_hexodecimal(unsigned int n)
{
    int count;
    char s[16] = "0123456789abcdef";

    count = 0;
    if(n < 16)
    {
        count += ft_putchar(s[n]);
    }
    else 
    {
        count += ft_hexodecimal(n / 16);
        count += ft_hexodecimal(n % 16);
    }
    return (count);
}

int ft_printf(const char *str, ... )
{
    va_list list;
    int i;
    int count;

    count = 0;
    i = 0;
    va_start(list, str);
    while(str[i] != '\0')
    {
        if(str[i] == '%' && str[i + 1] != '\0')
        {
            i++;
            if(str[i] == 'd')
            {
                count += ft_putnbr(va_arg(list, int));
            }
            else if(str[i] == 'x')
            {
                count += ft_hexodecimal(va_arg(list, unsigned int));
            }
            else if(str[i] == 's')
            {
                count += ft_putstr(va_arg(list, char *));
            }
            else
                write(1, &str[i], 1);
        }
        else if(str[i] != '%')
            count += write(1, &str[i], 1);
        i++;
    }
    va_end(list);
    return (count);
}
