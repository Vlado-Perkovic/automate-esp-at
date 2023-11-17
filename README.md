how to use it:

with a board:
cmake -DBOARD=<"ime plocice"> ..
make
./automate-esp-at 

without one (mocking):
cmake -DBOARD=MOCK ..
make
../esp32_mock.sh &
./automate-esp-at