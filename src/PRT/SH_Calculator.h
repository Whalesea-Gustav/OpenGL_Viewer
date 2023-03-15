#pragma once
#include <glm/glm.hpp>

#undef M_PI
#define M_PI 3.141592653589793f

class SHCoeffCalculator
{
public:
    static int GetIndex(int l, int m)
    {
        return l * (l + 1) + m;
    }

    static glm::vec3 ToVector(double phi, double theta)
    {
        double r = sin(theta);
        return glm::vec3(r * cos(phi), r * sin(phi), cos(theta));
    }

    static void ToSphericalCoords(const glm::vec3& dir, double& phi, double& theta)
    {
        theta = acos(dir.z);
        phi = atan2(dir.y, dir.x);
    }

    static double EvalSHBasis_HardCord(int l, int m, const glm::vec3& dir)
    {
        assert(l <= 4);

        switch (l) {
            case 0:
                return HardcodedSH00(dir);
            case 1:
                switch (m) {
                    case -1:
                        return HardcodedSH1n1(dir);
                    case 0:
                        return HardcodedSH10(dir);
                    case 1:
                        return HardcodedSH1p1(dir);
                }
            case 2:
                switch (m) {
                    case -2:
                        return HardcodedSH2n2(dir);
                    case -1:
                        return HardcodedSH2n1(dir);
                    case 0:
                        return HardcodedSH20(dir);
                    case 1:
                        return HardcodedSH2p1(dir);
                    case 2:
                        return HardcodedSH2p2(dir);
                }
            case 3:
                switch (m) {
                    case -3:
                        return HardcodedSH3n3(dir);
                    case -2:
                        return HardcodedSH3n2(dir);
                    case -1:
                        return HardcodedSH3n1(dir);
                    case 0:
                        return HardcodedSH30(dir);
                    case 1:
                        return HardcodedSH3p1(dir);
                    case 2:
                        return HardcodedSH3p2(dir);
                    case 3:
                        return HardcodedSH3p3(dir);
                }
            case 4:
                switch (m) {
                    case -4:
                        return HardcodedSH4n4(dir);
                    case -3:
                        return HardcodedSH4n3(dir);
                    case -2:
                        return HardcodedSH4n2(dir);
                    case -1:
                        return HardcodedSH4n1(dir);
                    case 0:
                        return HardcodedSH40(dir);
                    case 1:
                        return HardcodedSH4p1(dir);
                    case 2:
                        return HardcodedSH4p2(dir);
                    case 3:
                        return HardcodedSH4p3(dir);
                    case 4:
                        return HardcodedSH4p4(dir);
                }
        }
    }

    // Hardcoded spherical harmonic functions for low orders (l is first number
    // and m is second number (sign encoded as preceeding 'p' or 'n')).
    // As polynomials they are evaluated more efficiently in cartesian coordinates,
    // assuming that @d is unit. This is not verified for efficiency.
    static double HardcodedSH00(const glm::vec3& d) {
        // 0.5 * sqrt(1/pi)
        return 0.282095;
    }

    static double HardcodedSH1n1(const glm::vec3& d) {
        // -sqrt(3/(4pi)) * y
        return -0.488603 * d.y;
    }

    static double HardcodedSH10(const glm::vec3& d) {
        // sqrt(3/(4pi)) * z
        return 0.488603 * d.z;
    }

    static double HardcodedSH1p1(const glm::vec3& d) {
        // -sqrt(3/(4pi)) * x
        return -0.488603 * d.x;
    }

    static double HardcodedSH2n2(const glm::vec3& d) {
        // 0.5 * sqrt(15/pi) * x * y
        return 1.092548 * d.x * d.y;
    }

    static double HardcodedSH2n1(const glm::vec3& d) {
        // -0.5 * sqrt(15/pi) * y * z
        return -1.092548 * d.y * d.z;
    }

    static double HardcodedSH20(const glm::vec3& d) {
        // 0.25 * sqrt(5/pi) * (-x^2-y^2+2z^2)
        return 0.315392 * (-d.x * d.x - d.y * d.y + 2.0 * d.z * d.z);
    }

    static double HardcodedSH2p1(const glm::vec3& d) {
        // -0.5 * sqrt(15/pi) * x * z
        return -1.092548 * d.x * d.z;
    }

    static double HardcodedSH2p2(const glm::vec3& d) {
        // 0.25 * sqrt(15/pi) * (x^2 - y^2)
        return 0.546274 * (d.x * d.x - d.y * d.y);
    }

    static double HardcodedSH3n3(const glm::vec3& d) {
        // -0.25 * sqrt(35/(2pi)) * y * (3x^2 - y^2)
        return -0.590044 * d.y * (3.0 * d.x * d.x - d.y * d.y);
    }

    static double HardcodedSH3n2(const glm::vec3& d) {
        // 0.5 * sqrt(105/pi) * x * y * z
        return 2.890611 * d.x * d.y * d.z;
    }

    static double HardcodedSH3n1(const glm::vec3& d) {
        // -0.25 * sqrt(21/(2pi)) * y * (4z^2-x^2-y^2)
        return -0.457046 * d.y * (4.0 * d.z * d.z - d.x * d.x
                                    - d.y * d.y);
    }

    static double HardcodedSH30(const glm::vec3& d) {
        // 0.25 * sqrt(7/pi) * z * (2z^2 - 3x^2 - 3y^2)
        return 0.373176 * d.z * (2.0 * d.z * d.z - 3.0 * d.x * d.x
                                   - 3.0 * d.y * d.y);
    }

    static double HardcodedSH3p1(const glm::vec3& d) {
        // -0.25 * sqrt(21/(2pi)) * x * (4z^2-x^2-y^2)
        return -0.457046 * d.x * (4.0 * d.z * d.z - d.x * d.x
                                    - d.y * d.y);
    }

    static double HardcodedSH3p2(const glm::vec3& d) {
        // 0.25 * sqrt(105/pi) * z * (x^2 - y^2)
        return 1.445306 * d.z * (d.x * d.x - d.y * d.y);
    }

    static double HardcodedSH3p3(const glm::vec3& d) {
        // -0.25 * sqrt(35/(2pi)) * x * (x^2-3y^2)
        return -0.590044 * d.x * (d.x * d.x - 3.0 * d.y * d.y);
    }

    static double HardcodedSH4n4(const glm::vec3& d) {
        // 0.75 * sqrt(35/pi) * x * y * (x^2-y^2)
        return 2.503343 * d.x * d.y * (d.x * d.x - d.y * d.y);
    }

    static double HardcodedSH4n3(const glm::vec3& d) {
        // -0.75 * sqrt(35/(2pi)) * y * z * (3x^2-y^2)
        return -1.770131 * d.y * d.z * (3.0 * d.x * d.x - d.y * d.y);
    }

    static double HardcodedSH4n2(const glm::vec3& d) {
        // 0.75 * sqrt(5/pi) * x * y * (7z^2-1)
        return 0.946175 * d.x * d.y * (7.0 * d.z * d.z - 1.0);
    }

    static double HardcodedSH4n1(const glm::vec3& d) {
        // -0.75 * sqrt(5/(2pi)) * y * z * (7z^2-3)
        return -0.669047 * d.y * d.z * (7.0 * d.z * d.z - 3.0);
    }

    static double HardcodedSH40(const glm::vec3& d) {
        // 3/16 * sqrt(1/pi) * (35z^4-30z^2+3)
        double z2 = d.z * d.z;
        return 0.105786 * (35.0 * z2 * z2 - 30.0 * z2 + 3.0);
    }

    static double HardcodedSH4p1(const glm::vec3& d) {
        // -0.75 * sqrt(5/(2pi)) * x * z * (7z^2-3)
        return -0.669047 * d.x * d.z * (7.0 * d.z * d.z - 3.0);
    }

    static double HardcodedSH4p2(const glm::vec3& d) {
        // 3/8 * sqrt(5/pi) * (x^2 - y^2) * (7z^2 - 1)
        return 0.473087 * (d.x * d.x - d.y * d.y)
               * (7.0 * d.z * d.z - 1.0);
    }

    static double HardcodedSH4p3(const glm::vec3& d) {
        // -0.75 * sqrt(35/(2pi)) * x * z * (x^2 - 3y^2)
        return -1.770131 * d.x * d.z * (d.x * d.x - 3.0 * d.y * d.y);
    }

    static double HardcodedSH4p4(const glm::vec3& d) {
        // 3/16*sqrt(35/pi) * (x^2 * (x^2 - 3y^2) - y^2 * (3x^2 - y^2))
        double x2 = d.x * d.x;
        double y2 = d.y * d.y;
        return 0.625836 * (x2 * (x2 - 3.0 * y2) - y2 * (3.0 * x2 - y2));
    }

    static double Factorial(int x) {
        static const double factorial_cache[16] = {1, 1, 2, 6, 24, 120, 720, 5040,
                                                           40320, 362880, 3628800, 39916800,
                                                           479001600, 6227020800,
                                                           87178291200, 1307674368000};

        if (x < 16) {
            return factorial_cache[x];
        } else {
            double s = factorial_cache[15];
            for (int n = 16; n <= x; n++) {
                s *= n;
            }
            return s;
        }
    }

    static double DoubleFactorial(int x) {
        static const double dbl_factorial_cache[16] = {1, 1, 2, 3, 8, 15, 48, 105,
                                                               384, 945, 3840, 10395, 46080,
                                                               135135, 645120, 2027025};

        if (x < 16) {
            return dbl_factorial_cache[x];
        } else {
            double s = dbl_factorial_cache[16 - (x % 2 == 0 ? 2 : 1)];
            double n = x;
            while (n >= 16) {
                s *= n;
                n -= 2.0;
            }
            return s;
        }
    }

    static double EvalSHBasis_Formula(int l, int m, const glm::vec3& dir)
    {
        double phi, theta;
        ToSphericalCoords(dir, phi, theta);
        return EvalSHBasis_Formula(l, m, phi, theta);
    }

    static double K(int l, int m)
    {
        return sqrt((2.0 * l + 1) * Factorial(l - abs(m)) /
                    (4.0 * M_PI * Factorial(l + abs(m))));
    }

    static double EvalLegendrePolynomial(int l, int m, double x) {
        // Compute Pmm(x) = (-1)^m(2m - 1)!!(1 - x^2)^(m/2), where !! is the double
        // factorial.
        double pmm = 1.0;
        // P00 is defined as 1.0, do don't evaluate Pmm unless we know m > 0
        if (m > 0) {
            double sign = (m % 2 == 0 ? 1 : -1);
            pmm = sign * DoubleFactorial(2 * m - 1) * pow(1 - x * x, m / 2.0);
        }

        if (l == m) {
            // Pml is the same as Pmm so there's no lifting to higher bands needed
            return pmm;
        }

        // Compute Pmm+1(x) = x(2m + 1)Pmm(x)
        double pmm1 = x * (2 * m + 1) * pmm;
        if (l == m + 1) {
            // Pml is the same as Pmm+1 so we are done as well
            return pmm1;
        }
        // Use the last two computed bands to lift up to the next band until l is
        // reached, using the recurrence relationship:
        // Pml(x) = (x(2l - 1)Pml-1 - (l + m - 1)Pml-2) / (l - m)
        for (int n = m + 2; n <= l; n++) {
            double pmn = (x * (2 * n - 1) * pmm1 - (n + m - 1) * pmm) / (n - m);
            pmm = pmm1;
            pmm1 = pmn;
        }
        // Pmm1 at the end of the above loop is equal to Pml
        return pmm1;
    }

    static double EvalSHBasis_Formula(int l, int m, double phi, double theta)
    {
        double kml = K(l, m);
        if (m > 0) {
            return sqrt(2.0) * kml * cos(m * phi) *
                   EvalLegendrePolynomial(l, m, cos(theta));
        } else if (m < 0) {
            return sqrt(2.0) * kml * sin(-m * phi) *
                   EvalLegendrePolynomial(l, -m, cos(theta));
        } else {
            return kml * EvalLegendrePolynomial(l, 0, cos(theta));
        }
    }

};