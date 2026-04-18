#include<bits/stdc++.h>
using namespace std;

struct new_order{
    uint64_t order_id;
    char side;
    int32_t price;
    uint32_t quantity;
};

struct change_order{
    uint64_t order_id;
    int32_t new_price;
    uint32_t new_quantity;
};

struct cancel_order{
    uint64_t order_id;
};

class OrderBook{
    private:
        unordered_map<uint64_t , new_order>order_map;

        map<int32_t,uint64_t,greater<int32_t>>buys;
        map<int32_t,uint64_t>sells;

    public:
        void OnNewOrder(const new_order & order){
            order_map[order.order_id]=order;

            if(order.side=='B'){
                buys[order.price]+=order.quantity;
            }else{
                sells[order.price]+=order.quantity;
            }
        }
        void OnChangeOrder(const change_order& order){
            if(order_map.find(order.order_id) == order_map.end()){
                cout<<"Invalid order"<<endl;
                return;
            }

            auto  &old = order_map[order.order_id];

            if(old.side == 'B'){
                buys[old.price] -= old.quantity;
                if(buys[old.price] == 0) buys.erase(old.price);
            }else{
                sells[old.price] -= old.quantity;
                if(sells[old.price] == 0) sells.erase(old.price);
            }
            
            old.price = order.new_price;
            old.quantity = order.new_quantity;

            if(old.side == 'B'){
                buys[old.price] += old.quantity;
            }else{
                sells[old.price]+=old.quantity;
            }
        }
        void OnCancelOrder(const cancel_order& order){
            if(order_map.find(order.order_id) == order_map.end()) return;

            auto old = order_map[order.order_id];

            if(old.side=='B'){
                buys[old.price]-=old.quantity;
                if(buys[old.price]==0) buys.erase(old.price);
            }else{
                sells[old.price] -= old.quantity;
                if(sells[old.price] ==0) sells.erase(old.price);
            }

            order_map.erase(order.order_id);
        }

        void Print(){
            cout<<"Buys"<<endl;
            cout<<"Price Quantity"<<endl;

            for(auto& p : buys){
                cout<<p.first<<"    "<<p.second<<endl;
            }

            cout<<endl;

            cout<<"Sells"<<endl;
            cout<<"Price Quantity"<<endl;

            for(auto& p : sells){
                cout<<p.first<<"    "<<p.second<<endl;
            }
        }
};

int main(){
    OrderBook ob;

    ob.OnNewOrder({1, 'B', 100, 5000});
    ob.OnNewOrder({2, 'B', 100, 5000});
    ob.OnNewOrder({3, 'B', 99, 2000});
    ob.OnNewOrder({4, 'B', 98, 1000});

    ob.OnNewOrder({7, 'S', 102, 7000});
    ob.OnNewOrder({6, 'S', 103, 2000});
    ob.OnNewOrder({5, 'S', 104, 9000});

    cout<<"Initial Orderbook"<<endl;
    ob.Print();

    cout<<endl;


    ob.OnChangeOrder({3,90,4000});

    cout<<"After Change Order"<<endl;
    ob.Print();

    cout<<endl;

    ob.OnCancelOrder({6});

    cout<<"After cancel order"<<endl;

    ob.Print();






    



   

    return 0;




}
