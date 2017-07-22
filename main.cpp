#include "MicroBit.h"

MicroBit    uBit;
#define EVENT_ID    8888

int s1;
int s2;
int s3;
int s4;
int s5;
int s6;
int s7;
int s8;
int s9;
int s10;

ManagedString W1;
ManagedString W2;
ManagedString W3;
ManagedString W4;
ManagedString W5;
ManagedString W6;
ManagedString W7;
ManagedString W8;
ManagedString W9;
ManagedString W10;
ManagedString s;

int a = 0;
uint16_t b = 1;
bool pressed = false;
MicroBitImage smiley("0,255,0,255, 0\n0,255,0,255,0\n0,0,0,0,0\n255,0,0,0,255\n0,255,255,255,0\n");

void show() {
    while (pressed) {
		KeyValuePair* fd1 = uBit.storage.get("k1");
		KeyValuePair* fd2 = uBit.storage.get("k2");
		KeyValuePair* fd3 = uBit.storage.get("k3");
		KeyValuePair* fd4 = uBit.storage.get("k4");
		KeyValuePair* fd5 = uBit.storage.get("k5");
		KeyValuePair* fd6 = uBit.storage.get("k6");
		KeyValuePair* fd7 = uBit.storage.get("k7");
		KeyValuePair* fd8 = uBit.storage.get("k8");
		KeyValuePair* fd9 = uBit.storage.get("k9");
		KeyValuePair* fd10 = uBit.storage.get("k10");

		//this is not the first boot
		//      destination  source
        memcpy(&s1, fd1->value, sizeof(int));
        delete fd1;
		memcpy(&s2, fd2->value, sizeof(int));
        delete fd2;
		memcpy(&s3, fd3->value, sizeof(int));
        delete fd3;
		memcpy(&s4, fd4->value, sizeof(int));
        delete fd4;
		memcpy(&s5, fd5->value, sizeof(int));
        delete fd5;
		memcpy(&s6, fd6->value, sizeof(int));
        delete fd6;
		memcpy(&s7, fd7->value, sizeof(int));
        delete fd7;
		memcpy(&s8, fd8->value, sizeof(int));
        delete fd8;
		memcpy(&s9, fd9->value, sizeof(int));
        delete fd9;
		memcpy(&s10, fd10->value, sizeof(int));
        delete fd10;
				

		W1 = static_cast<char>(s1);
		if (W1 == "_") {
		} else {
			s = W1;
		}
		W2 = static_cast<char>(s2);
		if (W2 == '_') {
		} else {
			s = W1 + W2;
		}
		W3 = static_cast<char>(s3);
		if (W3 == '_') { 
		} else { 
			s = W1 + W2 + W3;
		}
		W4 = static_cast<char>(s4);
		if (W4 == '_') {
		} else {
			s = W1 + W2 + W3 + W4;
		}
		W5 = static_cast<char>(s5);
		if (W5 == '_') {
		} else {
			s = W1 + W2 + W3 + W4 + W5;
		}
		W6 = static_cast<char>(s6);
		if (W6 == '_') {
		} else {
			s = W1 + W2 + W3 + W4 + W5 + W6;
		}
		W7 = static_cast<char>(s7);
		if (W7 == '_') {
		} else {
			s = W1 + W2 + W3 + W4 + W5 + W6 + W7;
		}
		W8 = static_cast<char>(s8);
		if (W8 == '_') {
		} else {
			s = W1 + W2 + W3 + W4 + W5 + W6 + W7 + W8;
		}
		W9 = static_cast<char>(s9);
		if (W9 == '_') {
		} else {
			s = W1 + W2 + W3 + W4 + W5 + W6 + W7 + W8 + W9;
		}
		W10 = static_cast<char>(s10);
		if (W10 == '_') {
		} else {
			s = W1 + W2 + W3 + W4 + W5 + W6 + W7 + W8 + W9 + W10;
		}
				
			
		uBit.display.scrollAsync(s);
        uBit.sleep(50);
    }
}

char buffer [33];

void onControllerEvent(MicroBitEvent e) {
	a = e.value;

	if (a == 126) { //check end of sequence '~'
		uBit.display.print(smiley);
		uBit.sleep(500);
		b = 1;
		pressed = true;
		create_fiber(show);
		memset(buffer, 0, 0);

	} else { 
		pressed = false;
		itoa (b,buffer);
		ManagedString  str(buffer);
		uBit.storage.put("k" + str, (uint8_t *)&a, sizeof(int));
	
		b++;
	}
}


int main() {
    uBit.init();
    
	KeyValuePair* fd1 = uBit.storage.get("k1");

    if(fd1 != NULL)  {
        pressed = true;
		create_fiber(show);
    }
	
	uBit.messageBus.listen(EVENT_ID, 0, onControllerEvent);
	release_fiber();
}