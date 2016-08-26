#include <objects/ConvexHull.hpp>


#include <glm/glm.hpp>
#include <cstring>

namespace faod
{
    ConvexHull ConvexHull::boxHull(glm::vec2 wh)
    {
        ConvexHull c(4);
        c.points_[0] = glm::vec2(0.);
        c.points_[1] = glm::vec2(wh.x, 0);
        c.points_[2] = glm::vec2(wh.x, wh.y);
        c.points_[3] = glm::vec2(0., wh.y);
        return c;
    }
    ConvexHull ConvexHull::triHull(float w, float h)
    {
        ConvexHull c(3);
        c.points_[0] = glm::vec2(0.);
        c.points_[1] = glm::vec2(-(w/2.), h);
        c.points_[2] = glm::vec2( (w/2.), h);

        return c;
    }   

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

    glm::vec4 ConvexHull::getBoundingBox() const
    {
        if(len_ == 0)
        {
            return glm::vec4(0.);
        }

        float min_x, max_x, min_y, max_y;
        max_x = max_y = FLT_MIN;
        min_x = min_y = FLT_MAX;

        glm::vec2 v;

        for(unsigned int i = 0; i < len_; i++)
        {
            v = points_[i];

            if(v.x > max_x) max_x = v.x;
            if(v.x < min_x) min_x = v.x;

            if(v.y > max_y) max_y = v.y;
            if(v.y < min_y) min_y = v.y;
        }
        glm::vec4 res(min_x, min_y, max_x - min_x, max_y - min_y);
        return res;
    }

    bool ConvexHull::intersects(const ConvexHull &other) const
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
