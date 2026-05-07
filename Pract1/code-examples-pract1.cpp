// Приклад без використання патерну Strategy
// У цьому варіанті клас Order сам перевіряє тип доставки
// та самостійно обирає потрібний алгоритм розрахунку.

//#include <iostream>
//#include <string>
//
//class Order {
//public:
//    double calculateDelivery(const std::string& deliveryType, double distance) {
//        if (deliveryType == "standard") {
//            return 50 + distance * 5;
//        }
//        else if (deliveryType == "express") {
//            return 100 + distance * 10;
//        }
//        else if (deliveryType == "pickup") {
//            return 0;
//        }
//
//        return 0;
//    }
//};
//
//int main() {
//    Order order;
//
//    std::cout << "Standard delivery: "
//              << order.calculateDelivery("standard", 10) << std::endl;
//
//    std::cout << "Express delivery: "
//              << order.calculateDelivery("express", 10) << std::endl;
//
//    std::cout << "Pickup: "
//              << order.calculateDelivery("pickup", 10) << std::endl;
//
//    return 0;
//}


// Приклад з використанням патерну Strategy
// Кожен спосіб доставки винесено в окремий клас-стратегію.

//#include <iostream>
//
//class DeliveryStrategy {
//public:
//    virtual double calculate(double distance) = 0;
//    virtual ~DeliveryStrategy() {}
//};
//
//class StandardDelivery : public DeliveryStrategy {
//public:
//    double calculate(double distance) override {
//        return 50 + distance * 5;
//    }
//};
//
//class ExpressDelivery : public DeliveryStrategy {
//public:
//    double calculate(double distance) override {
//        return 100 + distance * 10;
//    }
//};
//
//class PickupDelivery : public DeliveryStrategy {
//public:
//    double calculate(double distance) override {
//        return 0;
//    }
//};
//
//class Order {
//private:
//    DeliveryStrategy* strategy;
//
//public:
//    void setStrategy(DeliveryStrategy* newStrategy) {
//        strategy = newStrategy;
//    }
//
//    double getDeliveryPrice(double distance) {
//        return strategy->calculate(distance);
//    }
//};
//
//int main() {
//    Order order;
//
//    StandardDelivery standard;
//    ExpressDelivery express;
//    PickupDelivery pickup;
//
//    order.setStrategy(&standard);
//    std::cout << "Standard delivery: "
//              << order.getDeliveryPrice(10) << std::endl;
//
//    order.setStrategy(&express);
//    std::cout << "Express delivery: "
//              << order.getDeliveryPrice(10) << std::endl;
//
//    order.setStrategy(&pickup);
//    std::cout << "Pickup: "
//              << order.getDeliveryPrice(10) << std::endl;
//
//    return 0;
//}


// Окремий фрагмент: інтерфейс Strategy та конкретні стратегії

#include <iostream>

class DeliveryStrategy {
public:
    virtual double calculate(double distance) = 0;
    virtual ~DeliveryStrategy() {}
};

class StandardDelivery : public DeliveryStrategy {
public:
    double calculate(double distance) override {
        return 50 + distance * 5;
    }
};

class ExpressDelivery : public DeliveryStrategy {
public:
    double calculate(double distance) override {
        return 100 + distance * 10;
    }
};

class PickupDelivery : public DeliveryStrategy {
public:
    double calculate(double distance) override {
        return 0;
    }
};


// Окремий фрагмент: Context, який використовує обрану стратегію

class DeliveryContext {
private:
    DeliveryStrategy* strategy;

public:
    DeliveryContext(DeliveryStrategy* selectedStrategy) {
        strategy = selectedStrategy;
    }

    void changeStrategy(DeliveryStrategy* selectedStrategy) {
        strategy = selectedStrategy;
    }

    double calculatePrice(double distance) {
        return strategy->calculate(distance);
    }
};


// Демонстрація роботи патерну Strategy

int main() {
    StandardDelivery standardDelivery;
    ExpressDelivery expressDelivery;
    PickupDelivery pickupDelivery;

    DeliveryContext context(&standardDelivery);

    std::cout << "Standard delivery price: "
              << context.calculatePrice(12) << std::endl;

    context.changeStrategy(&expressDelivery);

    std::cout << "Express delivery price: "
              << context.calculatePrice(12) << std::endl;

    context.changeStrategy(&pickupDelivery);

    std::cout << "Pickup delivery price: "
              << context.calculatePrice(12) << std::endl;

    return 0;
}