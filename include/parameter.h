#pragma once
#include "pargeo/point.h"
#include "pargeo/ball.h"

static const int dim = 4;
static double drange = 10;
static double noiseCut = 0;
static double depCut = 0;


using point = pargeo::point<dim>;
using ball = pargeo::_ball<dim, point>;
using pointD = pargeo::pointD<dim, int>;

