void main()
{
    char* video_mem = 0xb8000;
    *video_mem = 'X';
}