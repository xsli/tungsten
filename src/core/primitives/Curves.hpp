#ifndef CURVES_HPP_
#define CURVES_HPP_

#include "Primitive.hpp"

#include "bvh/BinaryBvh.hpp"

#include <memory>
#include <vector>

namespace Tungsten {

class Scene;

class Curves : public Primitive
{
    std::string _path;
    std::string _dir;

    uint32 _curveCount;
    uint32 _nodeCount;

    std::vector<uint32> _curveEnds;
    std::vector<Vec4f> _nodeData;
    std::vector<Vec3f> _nodeColor;

    std::shared_ptr<TriangleMesh> _proxy;

    Box3f _bounds;

    std::unique_ptr<BinaryBvh> _bvh;

    void loadCurves();
    void computeBounds();
    void buildProxy();

public:
    virtual ~Curves() {}

    Curves() = default;
    Curves(const Curves &o);

    virtual void fromJson(const rapidjson::Value &v, const Scene &scene) override;
    virtual rapidjson::Value toJson(Allocator &allocator) const override;

    virtual bool intersect(Ray &ray, IntersectionTemporary &data) const;
    virtual bool occluded(const Ray &ray) const;
    virtual bool hitBackside(const IntersectionTemporary &data) const;
    virtual void intersectionInfo(const IntersectionTemporary &data, IntersectionInfo &info) const;
    virtual bool tangentSpace(const IntersectionTemporary &data, const IntersectionInfo &info,
            Vec3f &T, Vec3f &B) const;

    virtual bool isSamplable() const;
    virtual void makeSamplable();
    virtual float inboundPdf(const IntersectionTemporary &data, const Vec3f &p, const Vec3f &d) const;
    virtual bool sampleInboundDirection(LightSample &sample) const;
    virtual bool sampleOutboundDirection(LightSample &sample) const;
    virtual bool invertParametrization(Vec2f uv, Vec3f &pos) const;

    virtual bool isDelta() const;
    virtual bool isInfinite() const;

    virtual float approximateRadiance(const Vec3f &p) const;
    virtual Box3f bounds() const;

    virtual const TriangleMesh &asTriangleMesh();

    virtual void prepareForRender();
    virtual void cleanupAfterRender();

    virtual Primitive *clone();
};

}

#endif /* CURVES_HPP_ */