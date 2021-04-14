#include"spline.h"
class Curve;
class Surface :public Spline{
public:
    Surface(){}

};

class SurfaceOfRevolution :public Surface{
public:
    SurfaceOfRevolution(Curve *c) : c(c) {}
    void Paint(ArgParser *args);
    TriangleMesh* OutputTriangles(ArgParser *args);

    int getNumVertices();
    Vec3f getVertex(int i);

    void OutputBSpline(FILE *file);
    void moveControlPoint(int selectedPoint, float x, float y);
    void addControlPoint(int selectedPoint, float x, float y);
    void deleteControlPoint(int selectedPoint);

private:
    Curve *c;

};

class BezierPatch :public Surface{
public:
    BezierPatch(){
    }
    void set(int i, const Vec3f &v) override { vertices[i] = v; }
    int getNumVertices() override { return 16; }
    Vec3f getVertex(int i) override { return vertices[i]; }
    void Paint(ArgParser *args);
    TriangleMesh* OutputTriangles(ArgParser *args);

private:
    Vec3f vertices[16];



};