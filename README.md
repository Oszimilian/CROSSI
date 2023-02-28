# Setup Repository

```
git submodule add https://github.com/xR3b0rn/dbcppp.git external/dbcppp
```

Wenn 'external/dbcppp/' schon als Submodule vorgemerkt ist bitte das machen:

```
git rm -r --cacked external/dbcppp
```

```
cd external/dbcppp/thrid-party

git submodule update --init --recursive
```



#Software Architektur

```mermaid
graph TD;
    Input -- List of CAN_Sockets --> DCU_Handler
    DCU_Handler[DCU_Handler] --> CAPTURE_MODE{Mode?};
    CAPTURE_MODE -- MULTI_THREAD_CAPTURE --> M[Starte Thread für jeden CAN];
    M --> S1[Thread für CAN1];
    M --> S2[Thread für CAN...]
    CAPTURE_MODE -- SINGLE_THREAD_CAPTURE --> S[Starte einen Thread für alle CAN's];
    S --> S3[Thread für CAN1-n]
    DCU_Handler --> F[Starte Thread für CAN_dbc]
    L[Linked-List CAN_Msg_List]
    S1 -- CAN Msg --> L;
    S2 -- CAN Msg --> L;
    S3 -- CAN MsG --> L;
    L -- CAN Msg --> F;
    DBC[.dbc-File]
    DBC --> F; 
    F --> Z[CAN to ROS];
    
```

