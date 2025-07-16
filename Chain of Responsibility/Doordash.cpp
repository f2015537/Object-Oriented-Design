#include<bits/stdc++.h>
using namespace std;

class OrderHandler {
    protected:
        OrderHandler* successor;
    public:
        OrderHandler(OrderHandler* successor): successor(successor) {}
        virtual void processOrder(const string& order) = 0;
        virtual ~OrderHandler(){
            cout << "OrderHandler base destructor called"<<endl;
            delete successor;
        }
};

class OrderValidationHandler : public OrderHandler {
    public:
        OrderValidationHandler(OrderHandler* successor): OrderHandler(successor) {}
        void processOrder(const string& order) override {
            cout<<"Validating order "<<order<<"\n";
            if(successor){
                successor->processOrder(order);
            }
        }
        ~OrderValidationHandler() override {
            cout<<"OrderValidationHandler dtor called"<<endl;
        }
};

class PaymentProcessingHandler : public OrderHandler {
    public:
        PaymentProcessingHandler(OrderHandler* successor) : OrderHandler(successor) {}

        void processOrder(const string& order) override {
            cout<<"Processing payment for order: "<<order<<endl;

            if(successor)
                successor->processOrder(order);
        }

        ~PaymentProcessingHandler() {
            cout<<"PaymentProcessingHanlder dtor called"<<endl;
        }
};

class OrderPreparationHandler : public OrderHandler {
    public:
        OrderPreparationHandler(OrderHandler* successor) : OrderHandler(successor) {}

        void processOrder(const string& order) override {
            cout<<"Preparing order: "<<order<<endl;

            if(successor)
                successor->processOrder(order);
        }
        ~OrderPreparationHandler() override {
            cout<<"OrderPreparationHandler dtor called"<<endl;
        }
};

class DeliveryAssignmentHandler : public OrderHandler {
    public:
        DeliveryAssignmentHandler(OrderHandler* successor) : OrderHandler(successor) {}

        void processOrder(const string& order) override {
            cout<<"Assigning delivery for order: "<<order<<endl;

            if(successor)
                successor->processOrder(order);
        }

        ~DeliveryAssignmentHandler() override {
            cout<<"DeliveryAssignmentHandler dtor called"<<endl;
        }
};

class OrderTrackingHandler : public OrderHandler {
    public:
        OrderTrackingHandler(OrderHandler* successor) : OrderHandler(successor) {}

        void processOrder(const string& order) override {
            cout<<"Tracking order: "<<order<<endl;

            if(successor)
                successor->processOrder(order);
        }

        ~OrderTrackingHandler() override {
            cout<<"OrderTrackingHandler dtor called"<<endl;
        }
};


int main(){
    // Create a chain of responsibility for order processing
        OrderHandler* orderTrackingHandler = new OrderTrackingHandler(nullptr);
        OrderHandler* deliveryAssignmentHandler = new DeliveryAssignmentHandler(orderTrackingHandler);
        OrderHandler* orderPreparationHandler = new OrderPreparationHandler(deliveryAssignmentHandler);
        OrderHandler* paymentProcessingHandler = new PaymentProcessingHandler(orderPreparationHandler);
        OrderHandler* orderValidationHandler = new OrderValidationHandler(paymentProcessingHandler);

        // Simulate an order being placed
        std::string order = "Burger and Fries";
        orderValidationHandler->processOrder(order);

        delete orderValidationHandler; // recursively deletes the entire chain
    return 0;
}