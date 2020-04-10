int main()
{
    int a = 0;
    int b = 56;
    for (int i = 10; i > 0; i--)
    {
        while (a <= 12)
        {
            a = a + 3 * b;
        }
        a = a + 6;
        if (a > 0)
        {
            a = 500;
        }
        else if (a == 500)
        {
            a =  -100;
        }
    }
    return a;
}