#include"spline.h"
//列优先存储
class Curve :public Spline{
public:
    Curve(int num_vertices) : num_vertices(num_vertices) {
        vertices.resize(num_vertices);
    }

    void Paint(ArgParser *args);
    void set(int i, const Vec3f &v) override { vertices[i] = v; }

    Vec3f getVertex(int i) override { return vertices[i]; }

    virtual void moveControlPoint(int selectedPoint, float x, float y){}
    virtual void addControlPoint(int selectedPoint, float x, float y){}
    virtual void deleteControlPoint(int selectedPoint){}


protected:
    void drawLines();
    void drawPoints();
    virtual void drawCurves(ArgParser *args) = 0;
    int num_vertices;
    std::vector<Vec3f> vertices;
};

class BezierCurve :public Curve{
public:
    BezierCurve(int num_vertices) : Curve(num_vertices) {}
    void OutputBezier(FILE *file);
    void OutputBSpline(FILE *file);
    TriangleMesh* OutputTriangles(ArgParser *args);

    int getNumVertices() override { return num_vertices; }
    Vec3f getVertex(int i) override { return vertices[i]; }

    void moveControlPoint(int selectedPoint, float x, float y);
    void addControlPoint(int selectedPoint, float x, float y);
    void deleteControlPoint(int selectedPoint);


private:
    void drawCurves(ArgParser *args);

};

class BSplineCurve :public Curve{
public:
    BSplineCurve(int num_vertices) : Curve(num_vertices) {}
    void OutputBezier(FILE *file);
    void OutputBSpline(FILE *file);
    TriangleMesh* OutputTriangles(ArgParser *args);

    int getNumVertices() override { return num_vertices; }
    Vec3f getVertex(int i) override { return vertices[i]; }

    void moveControlPoint(int selectedPoint, float x, float y);
    void addControlPoint(int selectedPoint, float x, float y);
    void deleteControlPoint(int selectedPoint);

private:
    void drawCurves(ArgParser *args);

};

