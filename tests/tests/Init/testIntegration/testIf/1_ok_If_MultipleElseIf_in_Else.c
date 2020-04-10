int main()
{
    int a = 23;
    if (a == 10)
    {
        a = 10;
    } else if (a < 11) {
        a = 11;
    } else if (a < 20) {
        a = 20;
    } else if (a < 22) {
        a = 22;
    } else {
        a = 1000;
    }
    return a;
}
