# samp-map-parser

Зависимости:

1. streamer
2. sscanf
3. strlib

Использование:
public OnGameModeInit()
{
    new virtualWorld = 5, interior = 1;
    MapParserLoad("text.pwn", virtualWorld, interior);
}