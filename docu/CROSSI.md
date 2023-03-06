```mermaid
graph LR;

Load_Config --> Handler
Check_DBC --> Check_Hash{Check_Hash}
Check_Hash -- yes --> Handler
Check_Hash -- no --> Rebuild_Code
Handler --> Check_DBC
Rebuild_Code --> Exit[Exit and rebuild catkin_ws]






subgraph HANDLER_CROSSI
    

    subgraph Capture_Thread

        CAN_Caputre


    end

    CAN_Caputre --> Msg_Ring_1
    Msg_Ring_1 --> CAN_Caputre
    
    CAN_DBC_Decode --> Msg_Ring_1
    Msg_Ring_1 --> CAN_DBC_Decode

    subgraph Decode_Thread

        CAN_DBC_Decode

    end

    CAN_DBC_Decode --> Msg_Ring_2
    Msg_Ring_2 --> CAN_DBC_Decode

    ROS_Publisher --> Msg_Ring_2
    Msg_Ring_2 --> ROS_Publisher

    subgraph Publisher_Thread

        ROS_Publisher

    end

    subgraph Capture_Thread
        rank=1;
    end


    subgraph Decode_Thread
        
    end


    subgraph Publisher_Thread
        
    end

end

    Handler

    Handler -- start --> HANDLER_CROSSI





```