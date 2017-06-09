#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>

#include <math.h>

namespace gazebo
{
  class ModelPush : public ModelPlugin
  {
  public:
      void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/);
      void OnUpdate(const common::UpdateInfo & /*_info*/);

  private:
      physics::ModelPtr model;
      physics::JointPtr J1;
      physics::JointPtr J2;
      physics::JointController *JCon;

      double i;

      event::ConnectionPtr updateConnection;
  };
}


