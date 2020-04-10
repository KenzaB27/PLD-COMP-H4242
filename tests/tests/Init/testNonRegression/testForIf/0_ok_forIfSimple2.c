int main()
{
    int a = 0;
    for (int i = 10; i > 0; i--)
    {
        if (a == 12)
        {
            a = 5;
        }
        else if (a == 5)
        {
            a = -6;
        }
        a = a + 6;
    }
    return a;
}