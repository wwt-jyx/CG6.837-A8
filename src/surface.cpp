#include"surface.h"
#include"curve.h"
void SurfaceOfRevolution::Paint(ArgParser *args)
{
    c->Paint(args);
}

int SurfaceOfRevolution::getNumVertices()
{
    return c->getNumVertices();
}

Vec3f SurfaceOfRevolution::getVertex(int i)
{
    return c->getVertex(i);
}

TriangleMesh *SurfaceOfRevolution::OutputTriangles(ArgParser *args) {
    return c->OutputTriangles(args);
}

void SurfaceOfRevolution::OutputBSpline(FILE *file) {
    c->OutputBSpline(file);
}

void SurfaceOfRevolution::moveControlPoint(int selectedPoint, float x, float y) {
    c->moveControlPoint(selectedPoint, x, y);
}

void SurfaceOfRevolution::addControlPoint(int selectedPoint, float x, float y) {
    c->addControlPoint(selectedPoint, x, y);
}

void SurfaceOfRevolution::deleteControlPoint(int selectedPoint) {
    c->deleteControlPoint(selectedPoint);
}

void BezierPatch::Paint(ArgParser *args)
{
    glPointSize(5);
    glColor3f(1, 0, 0);
    glBegin(GL_POINTS);
    for (Vec3f &v: vertices) {
        glVertex3f(v.x(), v.y(), v.z());
    }
    glEnd();




    glLineWidth(3);
    glColor3f(0, 1, 0);
    glBegin(GL_POINTS);
    int patch_tessellation = args->patch_tessellation;
    float d = 1.0f / patch_tessellation;
    vector<Matrix> G(4);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            G[i].Set(j, 0, vertices[i * 4 + j].x());
            G[i].Set(j, 1, vertices[i * 4 + j].y());
            G[i].Set(j, 2, vertices[i * 4 + j].z());
        }
    }
    for (int i = 0; i <= patch_tessellation; ++i) {
        float t = i * d;
        float t2 = t * t;
        float t3 = t2 * t;
        Matrix G_new;
        for (int j = 0; j < 4; ++j) {
            Vec4f T(t3, t2, t, 1);
            Bezier_Matrix.Transform(T);
            G[j].Transform(T);
            G_new.Set(j, 0, T.x());
            G_new.Set(j, 1, T.y());
            G_new.Set(j, 2, T.z());
        }
        for (int j = 0; j <= patch_tessellation; ++j) {
            float s = j * d;
            float s2 = s * s;
            float s3 = s2 * s;
            Vec4f S(s3, s2, s, 1);
            Bezier_Matrix.Transform(S);
            G_new.Transform(S);
            glVertex3f(S.x(), S.y(), S.z());
        }
    }
    glEnd();

    glLineWidth(5);
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_STRIP);
    for (Vec3f &v: vertices)
        glVertex3f(v.x(), v.y(),v.z());
    glEnd();
}

TriangleMesh *BezierPatch::OutputTriangles(ArgParser *args) {
    int patch_tessellation = args->patch_tessellation;
    float d = 1.0f / patch_tessellation;
    TriangleNet *triangleNet = new TriangleNet(patch_tessellation, patch_tessellation);
    vector<Matrix> G(4);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            G[i].Set(j, 0, vertices[i * 4 + j].x());
            G[i].Set(j, 1, vertices[i * 4 + j].y());
            G[i].Set(j, 2, vertices[i * 4 + j].z());
        }
    }
    for (int i = 0; i <= patch_tessellation; ++i) {
        float t = i * d;
        float t2 = t * t;
        float t3 = t2 * t;
        Matrix G_new;
        for (int j = 0; j < 4; ++j) {
            Vec4f T(t3, t2, t, 1);
            Bezier_Matrix.Transform(T);
            G[j].Transform(T);
            G_new.Set(j, 0, T.x());
            G_new.Set(j, 1, T.y());
            G_new.Set(j, 2, T.z());
        }
        for (int j = 0; j <= patch_tessellation; ++j) {
            float s = j * d;
            float s2 = s * s;
            float s3 = s2 * s;
            Vec4f S(s3, s2, s, 1);
            Bezier_Matrix.Transform(S);
            G_new.Transform(S);
            triangleNet->SetVertex(i, j, Vec3f(S.x(), S.y(), S.z()));
        }
    }
    return triangleNet;
}

