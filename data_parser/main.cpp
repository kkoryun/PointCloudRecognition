#include "kitti_parser.h"


int main()
{
    std::string KITTI_DATA_PATH = "C:/Project/2011_09_26_drive_0001_extract/2011_09_26/2011_09_26_drive_0001_extract";
    Parsers::KittiParser kittiParser;
    kittiParser.setFilePath(KITTI_DATA_PATH);
    std::vector<std::vector<KittiPoint> > data;
    kittiParser.readFiles(data, 20);

}