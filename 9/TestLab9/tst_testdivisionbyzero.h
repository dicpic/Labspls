#ifndef TST_TESTDIVISIONBYZERO_H
#define TST_TESTDIVISIONBYZERO_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <IKeypad.h>
#include <ILatch.h>
#include <lockcontroller.h>

using namespace testing;

class testKeypad:
public IKeypad{
public:
    MOCK_METHOD(bool, isActive, (), (override));
    MOCK_METHOD(void, wait, (), (override));
    MOCK_METHOD(PasswordResponse, requestPassword, (), (override));
};


class testLatch:
public ILatch{
public:
    MOCK_METHOD(bool, isActive, (), (override));
    MOCK_METHOD(DoorStatus, open, (), (override));
    MOCK_METHOD(DoorStatus, close, (), (override));
    MOCK_METHOD(DoorStatus, getDoorStatus, (), (override));
};


class GlobalTest:
public Test{
public:
    testKeypad keypad;
    testLatch latch;
    LockController* statusLock;
    void SetUp(){
        statusLock = new LockController(&keypad, &latch);
    }
    void TearDown(){

    }
};

TEST_F(GlobalTest, turnOnWait){

    EXPECT_CALL(keypad, wait())
            .Times(1)
            .WillOnce(Return());

    statusLock->wait();

}

TEST_F(GlobalTest, isDoorClosed){
    EXPECT_CALL(latch, getDoorStatus)
            .Times(1)
            .WillOnce(Return(DoorStatus::CLOSE));
    EXPECT_FALSE(statusLock->isDoorOpen());

}

TEST_F(GlobalTest, isDoorOpen){
    EXPECT_CALL(latch, getDoorStatus)
            .Times(1)
            .WillOnce(Return(DoorStatus::OPEN));
    EXPECT_TRUE(statusLock->isDoorOpen());

}

TEST_F(GlobalTest, unlockTestDoor){
    EXPECT_CALL(latch, open)
            .Times(1)
            .WillOnce(Return(DoorStatus::OPEN));
    EXPECT_EQ(statusLock->unlockDoor(), DoorStatus::OPEN);

}

TEST_F(GlobalTest, lockTestDoor){
    EXPECT_CALL(latch, close)
            .Times(1)
            .WillOnce(Return(DoorStatus::CLOSE));
    EXPECT_EQ(statusLock->lockDoor(), DoorStatus::CLOSE);

}

TEST_F(GlobalTest, hardWareTest){
    EXPECT_CALL(keypad, isActive)
            .Times(1)
            .WillOnce(Return(1));
    EXPECT_CALL(latch, isActive)
            .Times(1)
            .WillOnce(Return(1));
    EXPECT_EQ(statusLock->hardWareCheck(), HardWareStatus::OK);

}

TEST_F(GlobalTest, errorhardWareTest){
    delete statusLock;
    statusLock = new LockController(nullptr, &latch);
    EXPECT_CALL(keypad, isActive)
            .Times(AtLeast(0))
            .WillOnce(Return(1));
    EXPECT_CALL(latch, isActive)
            .Times(AtLeast(0))
            .WillOnce(Return(1));
    EXPECT_EQ(statusLock->hardWareCheck(), HardWareStatus::ERROR);

}

TEST_F(GlobalTest, LatchTest){
    EXPECT_CALL(keypad, isActive)
            .Times(AtLeast(0))
            .WillOnce(Return(1));
    EXPECT_CALL(latch, isActive)
            .Times(AtLeast(0))
            .WillOnce(Return(0));
    EXPECT_EQ(statusLock->hardWareCheck(), HardWareStatus::ERROR);

}

TEST_F(GlobalTest, PasswordTest){
    PasswordResponse pass;
    pass.password = "0000";
    pass.status = PasswordResponse::Status::OK;
    EXPECT_CALL(keypad, requestPassword)
            .Times(1)
            .WillOnce(Return(pass));
    EXPECT_TRUE(statusLock->isCorrectPassword());
}

TEST_F(GlobalTest, WrongPasswordTest){
    PasswordResponse pass;
    pass.password = "1234";
    pass.status = PasswordResponse::Status::OK;
    EXPECT_CALL(keypad, requestPassword)
            .Times(1)
            .WillOnce(Return(pass));
    EXPECT_FALSE(statusLock->isCorrectPassword());
}

TEST_F(GlobalTest, ChangePasswordTest){
    PasswordResponse pass_old, pass_new, user_input;
    pass_old.password = "0000";
    pass_old.status = PasswordResponse::Status::OK;
    user_input.password = "1111";
    user_input.status = PasswordResponse::Status::OK;
    pass_new.password = "1111";
    pass_new.status = PasswordResponse::Status::OK;
    EXPECT_CALL(keypad, requestPassword)
            .Times(3)
            .WillOnce(Return(pass_old))
            .WillOnce(Return(user_input))
            .WillOnce(Return(pass_new));
    statusLock->resetPassword();
    EXPECT_TRUE(statusLock->isCorrectPassword());
}

TEST_F(GlobalTest, ChangePasswordWith){
    PasswordResponse pass_old, pass_new1, user_input1, pass_new2, user_input2;
    pass_old.password = "0000";
    pass_old.status = PasswordResponse::Status::OK;
    user_input1.password = "9876";
    user_input1.status = PasswordResponse::Status::OK;
    pass_new1.password = "9876";
    pass_new1.status = PasswordResponse::Status::OK;
    user_input2.password = "1111";
    user_input2.status = PasswordResponse::Status::OK;
    pass_new2.password = "1111";
    pass_new2.status = PasswordResponse::Status::OK;
    EXPECT_CALL(keypad, requestPassword)
            .Times(5)
            .WillOnce(Return(pass_old))
            .WillOnce(Return(user_input1))
            .WillOnce(Return(pass_new1))
            .WillOnce(Return(user_input2))
            .WillOnce(Return(pass_new2));
    statusLock->resetPassword();
    statusLock->resetPassword();
    EXPECT_TRUE(statusLock->isCorrectPassword());
}

#endif TST_TESTDIVISIONBYZERO_H
