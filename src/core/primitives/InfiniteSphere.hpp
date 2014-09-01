#ifndef INFINITESPHERE_HPP_
#define INFINITESPHERE_HPP_

#include "Primitive.hpp"

namespace Tungsten {

class InfiniteSphere : public Primitive
{
    Mat4f _rotTransform;
    Mat4f _invRotTransform;
    bool _doSample;

    std::shared_ptr<TriangleMesh> _proxy;

    Vec2f directionToUV(const Vec3f &wi) const;
    Vec2f directionToUV(const Vec3f &wi, float &sinTheta) const;
    Vec3f uvToDirection(Vec2f uv, float &sinTheta) const;
    void buildProxy();

public:
    InfiniteSphere();

    void fromJson(const rapidjson::Value &v, const Scene &scene) override;
    rapidjson::Value toJson(Allocator &allocator) const override;

    virtual bool intersect(Ray &ray, IntersectionTemporary &data) const override;
    virtual bool occluded(const Ray &ray) const override;
    virtual bool hitBackside(const IntersectionTemporary &data) const override;
    virtual void intersectionInfo(const IntersectionTemporary &data, IntersectionInfo &info) const override;
    virtual bool tangentSpace(const IntersectionTemporary &data, const IntersectionInfo &info,
            Vec3f &T, Vec3f &B) const override;

    virtual bool isSamplable() const override;
    virtual void makeSamplable() override;
    virtual float inboundPdf(const IntersectionTemporary &data, const Vec3f &p, const Vec3f &d) const override;
    virtual bool sampleInboundDirection(LightSample &sample) const override;
    virtual bool sampleOutboundDirection(LightSample &sample) const override;
    virtual bool invertParametrization(Vec2f uv, Vec3f &pos) const override;

    virtual bool isDelta() const override;
    virtual bool isInfinite() const override;

    virtual float approximateRadiance(const Vec3f &p) const override;
    virtual Box3f bounds() const override;

    virtual const TriangleMesh &asTriangleMesh() override;

    virtual void prepareForRender() override;
    virtual void cleanupAfterRender() override;

    virtual Primitive *clone() override;
};

}

#endif /* INFINITESPHERE_HPP_ */