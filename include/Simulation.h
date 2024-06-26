#pragma once

#include <vector>

#include "Box.h"
#include "Particle.h"
#include "Vector.h"

#include "constants.h"

class Simulation {
  std::vector<Particle> gas_;
  Box box_;
  std::vector<std::vector<Particle *>> grid_;
  double p_;
  double v_avg_;
  double E_;
  double kT_;
  double V_;
  double b_;

public:
  Simulation(std::vector<Particle> &gas, Box &box);

  ~Simulation() = default;

  void RandomSpawn();

  void ResetThermodynamicValues();

  std::vector<Particle> &GetGas();

  void AddParticle(const Particle &molecule);

  void RemoveParticle();

  void BoxCollision(Particle *curr);

  void ParticleCollision(Particle *curr, Particle *other);

  void ManageCollisionsLinear();

  void ManageCollisionsSquared();

  void MoveParticles(double timeStep);

  friend class MainWidget;
};

Vector AbsolutelyElasticCollision(const Vector &t, const Vector &v1,
                                  const Vector &v1_n, const Vector &v2_n,
                                  double m1, double m2);