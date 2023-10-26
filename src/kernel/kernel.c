char hell_yeh()
{
    return 'Y';
}

void entry_point()
{
    char* video_memory = (char*) 0xb8000;
    *video_memory = hell_yeh();

    while(1) {}
}