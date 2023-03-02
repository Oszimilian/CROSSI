#ifndef MSGGEN_H
#define MSGGEN_H



namespace dcu
{
    class DCU_Handler;

    class Msggen
    {
        public:
            Msggen(DCU_Handler *handler);

        private:
            DCU_Handler *handler;

            

    };
}

#endif