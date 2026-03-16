//
// Created by miguelgarc5605 on 3/16/26.
//

#ifndef PROJECTBRICK_GLUTILS_H
#define PROJECTBRICK_GLUTILS_H
#include "NormalizedPoint.h"
#include "Point.h"


struct GLUtils {

    // converts a point from pixel space to normalized GL space
    static NormalizedPoint convertPointToNormalizedPoint(Point point, float windowSize) {
        float m = (2.0f/windowSize);
        float normalizedX = (m * point.x) - 1.0f;
        float normalizedY = -1 * ((m * point.y) - 1.0f);

        NormalizedPoint output{};
        output.x = normalizedX;
        output.y = normalizedY;

        return output;
    }

};


#endif //PROJECTBRICK_GLUTILS_H