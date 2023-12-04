#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Vehicle.h"

class FakeUnit : public Unit {
public:
  float GetPositionX() const override { return 0.0f; }
  float GetPositionY() const override { return 0.0f; }
  float GetPositionZ() const override { return 0.0f; }
  float GetOrientation() const override { return 0.0f; }
};

class MockVehicleEntry : public VehicleEntry {
public:
  MOCK_METHOD(std::string, GetName, (), (const, override));
};

class StubTransportBase : public TransportBase {
public:
  MOCK_METHOD(void, CalculatePassengerPosition, (float& x, float& y, float& z, float* o), (const, override));
  MOCK_METHOD(void, CalculatePassengerOffset, (float& x, float& y, float& z, float* o), (const, override));
};

TEST(VehicleTest, FakeTest) {
  FakeUnit fakeUnit;

  EXPECT_EQ(fakeUnit.GetPositionX(), 0.0f);
  EXPECT_EQ(fakeUnit.GetPositionY(), 0.0f);
  EXPECT_EQ(fakeUnit.GetPositionZ(), 0.0f);
  EXPECT_EQ(fakeUnit.GetOrientation(), 0.0f);
}

TEST(VehicleTest, MockTest) {
  MockVehicleEntry mockVehicleEntry;

  EXPECT_CALL(mockVehicleEntry, GetName()).WillOnce(::testing::Return("MockName"));

  EXPECT_EQ(mockVehicleEntry.GetName(), "MockName");
}

TEST(VehicleTest, StubTest_CalculatePassengerPosition) {
  StubTransportBase stubTransportBase;

  float expectedX = 0.0f, expectedY = 0.0f, expectedZ = 0.0f, expectedO = 0.0f;
  EXPECT_CALL(stubTransportBase, CalculatePassengerPosition(_, _, _, _))
      .WillOnce(::testing::DoAll(::testing::SetArgReferee<0>(expectedX),
                                 ::testing::SetArgReferee<1>(expectedY),
                                 ::testing::SetArgReferee<2>(expectedZ),
                                 ::testing::SetArgReferee<3>(expectedO)));

  float x = 1.0f, y = 2.0f, z = 3.0f, o = 4.0f;
  stubTransportBase.CalculatePassengerPosition(x, y, z, &o);

  EXPECT_EQ(x, expectedX);
  EXPECT_EQ(y, expectedY);
  EXPECT_EQ(z, expectedZ);
  EXPECT_EQ(o, expectedO);
}

TEST(VehicleTest, StubTest_CalculatePassengerOffset) {
  StubTransportBase stubTransportBase;

  float expectedX = 0.0f, expectedY = 0.0f, expectedZ = 0.0f, expectedO = 0.0f;
  EXPECT_CALL(stubTransportBase, CalculatePassengerOffset(_, _, _, _))
      .WillOnce(::testing::DoAll(::testing::SetArgReferee<0>(expectedX),
                                 ::testing::SetArgReferee<1>(expectedY),
                                 ::testing::SetArgReferee<2>(expectedZ),
                                 ::testing::SetArgReferee<3>(expectedO)));

  float x = 1.0f, y = 2.0f, z = 3.0f, o = 4.0f;
  stubTransportBase.CalculatePassengerOffset(x, y, z, &o);

  EXPECT_EQ(x, expectedX);
  EXPECT_EQ(y, expectedY);
  EXPECT_EQ(z, expectedZ);
  EXPECT_EQ(o, expectedO);
}


TEST(VehicleTest, SimpleTest) {
  FakeUnit fakeUnit;

  float expectedX = 10.0f, expectedY = 20.0f, expectedZ = 30.0f, expectedO = 45.0f;
  fakeUnit.SetPosition(expectedX, expectedY, expectedZ, expectedO);

  Vehicle vehicle(&fakeUnit);
  float distance = vehicle.ComputeDistanceFromOrigin();

  EXPECT_EQ(distance, sqrt(expectedX * expectedX + expectedY * expectedY + expectedZ * expectedZ));
}