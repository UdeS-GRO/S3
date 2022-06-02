% MotionGenesis file:  MGTemplateBasic.txt
% Copyright (c) 2009-2017 Motion Genesis LLC.  Only for use with MotionGenesis.
%--------------------------------------------------------------------
%   Physical objects.
NewtonianFrame  N                % Newtonian reference frame
RigidBody       A                % Technical name of body
RigidFrame      B                % Comment
Particle        Q                % Comment
Point           O( B )           % Comment.
%--------------------------------------------------------------------
%   Mathematical declarations.
Variable    qA''                 % qA and its 1st and 2nd derivatives.
Variable    Fx, Fy               % Reaction forces
Constant    g = 9.80665 m/s^2    % Earth's gravitational acceleration
Specified   TA                   % Torque on A from N
%--------------------------------------------------------------------
%   Mass and inertia properties.
A.SetMass( mA = 2 kg )
Q.SetMass( mQ = 3 kg )
A.SetInertia( Acm,  IAxx = 0.2 kg*m^2,  IAyy = 0.3 kg*m^2,  IAzz = 0.4 kg*m^2 )
B.SetInertia( Bcm,  IBxx, IByy, IBzz,  IBxy, IByz, IBzx )
%--------------------------------------------------------------------
%   Rotational kinematics.
A.RotateX( N, qA )
B.RotateNegativeY( A, t )
B.SetAngularVelocity( N, someVector> )
%--------------------------------------------------------------------
%   Translational kinematics.
Q.SetPosition( No, positionVector> )
Q.Translate( No, positionVector> )          % Sets position, velocity, acceleration
Q.SetVelocityAcceleration( N, velVector> )  % Differentiates to find acceleration
%--------------------------------------------------------------------
%   Motion constraints (if any).
MotionConstraint[1] = u2 - u1
MotionConstraint[2] = Dot( Q.GetVelocity(N), Ax> )
MotionConstraint[3] = Dot( Q.GetVelocity(N), Ay> )
SolveDt( MotionConstraint, u3, u4, u5 )
%--------------------------------------------------------------------
%   Add relevant contact/distance forces.
System.AddForceGravity( -g*Ny> )
Q.AddForce( someVector> )                   % External force
Q.AddForce( P, actionReactionForce> )       % Law of action/reaction
%--------------------------------------------------------------------
%   Add relevant torques.
A.AddTorque( SomeVector> )                  % External torque
B.AddTorque( A, actionReactionTorque> )     % Law of action/reaction
%--------------------------------------------------------------------
%   F = m*a    (translational equations of motion).
Dynamics[1] = Dot(  B.GetDynamics(),  Nx>  )
Dynamics[2] = Dot(  B.GetDynamics(),  Ny>  )
%--------------------------------------------------------------------
%   M = DH/Dt  (rotational equations of motion).
Dynamics[3] = Dot(  B.GetDynamics(Bcm),  Bz>  )
%--------------------------------------------------------------------
%   Solve linear equations for list of unknowns.
Solve( Dynamics,  x'', y'', Fx, Fy )
%--------------------------------------------------------------------
%   Initial values for variables (e.g., for ODE command).
Input  qA = 30 deg,  qA' = 0 rad/sec
Input  qB = 90 deg,  qB' = 0 rad/sec
%--------------------------------------------------------------------
%   Other calculations (distance, energy, momentum, etc.).
xQ = Dot(  Q.GetPosition(No),  Nx>  )
KineticEnergy = System.GetKineticEnergy()
GravityPotentialEnergy = System.GetForceGravityPotentialEnergy( -g*Ny>, No )
MechanicalEnergy = KineticEnergy + GravityPotentialEnergy
H> = System.GetAngularMomentum( aboutPoint )
L> = EvaluateAtInput( System.GetLinearMomentum() )
%--------------------------------------------------------------------
%   List output quantities (e.g., for ODE command).
Output      t sec,  x m,  Fx Newton,  Fy Newton
OutputPlot  t sec,  qA degrees  qB degrees
%--------------------------------------------------------------------
%   Solve ODEs (or auto-generate MATLAB, C, Fortran, ... code).
Input  tFinal = 10 sec,  tStep = 0.02 sec,  absError = 1.0E-08
ODE()  Filename    % or ODE( Zero, listOfVariablesToSolve ) Filename.m
%--------------------------------------------------------------------
%   Record input together with responses.
Save  someFileName.html
Quit

