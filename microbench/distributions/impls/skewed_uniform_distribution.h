//
// Created by Ravil Galiev on 30.08.2022.
//

#ifndef SETBENCH_SKEWED_UNIFORM_DISTRIBUTION_H
#define SETBENCH_SKEWED_UNIFORM_DISTRIBUTION_H

#include <algorithm>
#include <cassert>
#include "random_xoshiro256p.h"
#include "plaf.h"
#include "distributions/distribution.h"
//#include "parameters/skewed_set_parameters.h"

class SkewedUniformDistribution : public Distribution {
private:
    PAD;
    Random64 *rng;
    Distribution *hotDistribution;
    Distribution *coldDistribution;
    double hotProb;
    size_t hotSetLength;
    PAD;
public:
    SkewedUniformDistribution(Distribution *_hotDistribution, Distribution *_coldDistribution,
                              Random64 *_rng, const double _hotProb, const size_t _hotSetLength)
            : hotDistribution(_hotDistribution), coldDistribution(_coldDistribution),
              rng(_rng), hotProb(_hotProb), hotSetLength(_hotSetLength) {}


//    SkewedUniformDistribution(Random64 *_rng, SkewedUniformParameters *parameters, const size_t range)
//            : rng(_rng) {
//        hotDistribution = parameters->hotDistBuilder->getDistribution(rng, parameters->getHotLength(range));
//        coldDistribution = parameters->coldDistBuilder->getDistribution(rng, parameters->getColdLength(range));
//        hotProb = parameters->hotProb;
//        hotSetLength = parameters->getHotLength(range);
//    }

    size_t next() {
        size_t value;
        double z; // Uniform random number (0 < z < 1)
        // Pull a uniform random number (0 < z < 1)
        do {
            z = ((double) rng->next() / (double) rng->max_value);
        } while ((z == 0) || (z == 1));
        if (z < hotProb) {
            value = hotDistribution->next();
        } else {
            value = hotSetLength + coldDistribution->next();
        }
        return value;
    }

    ~SkewedUniformDistribution() {
        delete hotDistribution;
        delete coldDistribution;
    }
};


#endif //SETBENCH_SKEWED_UNIFORM_DISTRIBUTION_H
