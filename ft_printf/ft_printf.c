#include <stdarg.h>
#include <unistd.h>

void put_str(char *str, int *len)
{
    if(!str)
        str = "(null)";
    while(*str)
        *len += write(1, str++, 1);
}

void    put_nbr(long long int nbr, int base, int *len)
{
    char *hex;

    hex = "0123456789abcdef";
    if(nbr < 0)
    {
        nbr *= -1;
        *len += write(1, "-", 1);
    }
    if(nbr >= base)
    {
        put_nbr((nbr / base), base, len);
        *len += write(1, &hex[nbr % base], 1);
    }
}

int ft_printf(const char *format, ...)
{
    int len;
    va_list *ptr;

    len = 0;
    va_start(ptr, format);
    while(*format)
    {
        if((*format == '%') && *(format + 1))
        {
            format++;
            if(*format == 's')
                put_str(va_arg(ptr, char *), &len);
            else if(*format == 'd')
                put_nbr((long long int)va_arg(ptr, int), 10, &len);
            else if(*format == 'x')
                put_nbr((long long int)va_arg(ptr, unsigned int), 16, &len);
        }
        else
            len += write(1, format, 1);
        format++;
    }
    return(va_end(ptr), len);
}

int main ()
{
    char *s = "abcasda";
    int a = 12415125;
    ft_printf("beinm ardmı = %s, beinm yaşsim = %d\n", s, a);
}