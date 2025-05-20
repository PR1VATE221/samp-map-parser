#include            <streamer>
#include            <sscanf2>
#include			<strlib.inc>

static RemoveQuotes(string[])
{
    new length = strlen(string);
    if (length > 0 && string[0] == '"') 
    {
        strdel(string, 0, 1);
        length--; 
    }
    if (length > 0 && string[length-1] == '"') 
    {
        string[length-1] = '\0';
    }
}

stock MapParserLoad(const filename[], virtualWorld, interior) {
    new File:file = fopen(filename, io_read);
    new tmpobjid;

    new line[512];
    while (fread(file, line)) {
        if (line[0] == ';' || line[0] == '\0') continue;
        if (strfind(line, "CreateDynamicObject") != -1) {
            new pos = strfind(line, "(");
            // if (pos == -1) continue;

            // Парсим только до object_world
            new modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz;
            sscanf(line[pos + 1], "p<,>iffffff", modelid, x, y, z, rx, ry, rz);

            tmpobjid = CreateDynamicObject(modelid, x, y, z, rx, ry, rz, virtualWorld, interior, -1, 300.000, 300.000);
            
        }

        if (strfind(line, "SetDynamicObjectMaterial") != -1) {
            new pos = strfind(line, "(");
            if (pos == -1) continue;

            new plug[10], materialindex, modelid, txdname[32], texturename[32], color;

            new endpos = strfind(line, ")", false, pos);
            if (endpos != -1) line[endpos] = '\0';

            sscanf(line[pos + 1], "p<,>s[10]iis[32]s[32]x", plug, materialindex, modelid, txdname, texturename, color);

            RemoveQuotes(txdname);
            RemoveQuotes(texturename);

            strtrim(txdname);
            strtrim(texturename);

            SetDynamicObjectMaterial(tmpobjid, materialindex, modelid, txdname, texturename, color);
            
        }
    }

    fclose(file);

    printf("[Mapping Connector] Загружен файл маппинга \"%s\"", filename);
}

main() {
    MapParserLoad("Test.inc", 0, 0);
}
