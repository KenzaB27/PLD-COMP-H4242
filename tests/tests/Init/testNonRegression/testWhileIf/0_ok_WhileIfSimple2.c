int main()
{
    int a = 0;
    int b = 10;
    while (a < b)
    {
        a = a+3;
        if (a ==18)
        {
            a = -6;
        }
        else if ( a == -6)
        {
            b = 30;
        }
    }

    return a;
}