#include "model_push.hh"

namespace gazebo
{
void ModelPush::Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
{
    this->model = _parent;
    this->model->SetGravityMode(true);

    J1 = this->model->GetJoint("joint1");
    J2 = this->model->GetJoint("joint2");

    J1->SetProvideFeedback(true);
    J2->SetProvideFeedback(true);

    JCon = new physics::JointController(model);

    JCon->AddJoint(J1);
    JCon->AddJoint(J2);
    JCon->SetPositionPID(J1->GetScopedName(), common::PID(100, 0.01, 50));
    JCon->SetPositionPID(J2->GetScopedName(), common::PID(100, 0.01, 50));

    JCon->SetVelocityPID(J1->GetScopedName(), common::PID(80, 0.01, 20));
    JCon->SetVelocityPID(J2->GetScopedName(), common::PID(80, 0.01, 20));

    JCon->SetJointPosition(J1, 0);
    JCon->SetJointPosition(J2, 0);
    JCon->Update();

    i = 0;

    std::cout << "Hey" << std::endl;
    this->updateConnection = event::Events::ConnectWorldUpdateBegin(boost::bind(&ModelPush::OnUpdate, this, _1));
}

void ModelPush::OnUpdate(const common::UpdateInfo & /*_info*/)
{
    i = i + 0.01;
    JCon->SetPositionTarget(J1->GetScopedName(), 0.785*sin(M_PI*i/100));
    JCon->SetPositionTarget(J2->GetScopedName(), -0.785*sin(M_PI*i/100));
    JCon->Update();
}

GZ_REGISTER_MODEL_PLUGIN(ModelPush)
}

