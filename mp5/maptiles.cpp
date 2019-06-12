/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"
#include <vector>

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
     int col = theSource.getColumns();
     int row = theSource.getRows();
     MosaicCanvas * ret = new MosaicCanvas(row, col);
     vector<Point<3>> vect;
     map<Point<3>, TileImage*> tilemap;
     for (vector<TileImage>::iterator i = theTiles.begin(); i!=theTiles.end();++i){
       LUVAPixel pix = i->getAverageColor();
       Point<3> temppoint = convertToXYZ(pix);
       tilemap.insert(pair<Point<3>, TileImage*>(temppoint, &(*i)));
       vect.push_back(temppoint);
     }
     KDTree<3> tilestree = KDTree<3>(vect);

     for(int i = 0; i<row; i++){
       for (int j = 0; j<col; j++){
         LUVAPixel pix = theSource.getRegionColor(i,j);
         Point<3> temppoint = convertToXYZ(pix);
         Point<3> neighbor = tilestree.findNearestNeighbor(temppoint);
         ret->setTile(i,j,tilemap[neighbor]);
       }
     }
    return ret;
}
