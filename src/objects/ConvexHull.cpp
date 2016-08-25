#include <objects/ConvexHull.hpp>


#include <glm/glm.hpp>
#include <cstring>

namespace faod
{
    ConvexHull::ConvexHull(unsigned int len) : len_(len), points_(nullptr)
    {
        if(len_ > 0)
        {
            points_ = new glm::vec2[len];
        }
    }
    ConvexHull::ConvexHull(unsigned int len, glm::vec2 *points) : ConvexHull(len) 
    {
        if(len_)
        {
            memcpy(points_, points, len_ * sizeof(glm::vec2));
        }
    }
    ConvexHull::ConvexHull(const ConvexHull& c) : ConvexHull(c.len_, c.points_)
    {
    }

    ConvexHull::~ConvexHull()
    {
        delete[] points_;
        points_ = nullptr;
        len_    = 0;
    }

    void ConvexHull::translate(glm::vec2 tr)
    {
        for(unsigned int i = 0; i < len_; i++)
        {
            points_[i] += tr;
        }
    }
    void ConvexHull::rotate(float orient)
    {
        if(orient != 0)
        {
            float s, c;
            c = cos(orient);
            s = sin(orient);

            glm::mat2 rotm(c, s, -s, c);

            for(unsigned int i = 0; i < len_; i++)
            {
                points_[i] = rotm * points_[i];
            }
        }
    }

    bool ConvexHull::intersects(const ConvexHull &other)
    {
        bool isIn;
        float sign;
        unsigned int i, j;

        glm::vec2 pA, pB, pC;
        glm::vec2 vAB, vAC;

        //for each points of the other hull
        for(i = 0; i < other.len_; i++)
        {
            //test if the point is at the right (-1) or at the left (+1)
            //of a segment made from two points of this hull
            pA = points_[len_ - 1];
            pB = points_[0];
            pC = other.points_[i];

            vAB = pB - pA;
            vAC = pC - pA;

            sign = m_sign(vAB.x * vAC.y - vAB.y * vAC.x);
            isIn = true;

            //for each segment of this hull
            for(j = 0; j < len_ - 1; j++)
            {
                pA = points_[j];
                pB = points_[j + 1];

                vAB = pB - pA;
                vAC = pC - pA;

                if(sign != m_sign(vAB.x * vAC.y - vAB.y * vAC.x))
                {
                    isIn = false; //it is not inside this hull
                    break;
                }
            }
            if(isIn)
            {
                return true;
            }
        }
        return false;
    }

}
