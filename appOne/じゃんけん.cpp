#if 1
#include"libOne.h"
struct HAND {
    int hand;
    int img[3];
    float px, py, angle;
    float r, g, b;
    int life;
};

struct DATA {
    int INIT = 0;
    int PLAY = 1;
    int RESULT = 2;
    int state = INIT;

    int GU = 0;
    int CHOKI = 1;
    int PA = 2;
    struct HAND player;
    struct HAND pc;
    int heartImg;

    float resultSize;

};

void loadImages(struct DATA* d) {
    d->player.img[0] = loadImage("assets\\playerGu.png");
    d->player.img[1] = loadImage("assets\\playerCHOKI.png");
    d->player.img[2] = loadImage("assets\\playerPA.png");
    d->pc.img[0] = loadImage("assets\\pcGu.png");
    d->pc.img[1] = loadImage("assets\\pcCHOKI.png");
    d->pc.img[2] = loadImage("assets\\pcPA.png");
    d->heartImg = loadImage("assets\\heart.png");

}
void init(struct DATA* d) {
    d->player.hand = d->GU;
    d->player.px = 250;
    d->player.py = 225;
    d->player.angle = 0;
    d->player.r = 255;
    d->player.g = 255;
    d->player.b= 255;
    d->player.life = 3;


    d->pc.hand = d->GU;
    d->pc.px = 800-250;
    d->pc.py = 225;
    d->pc.angle = 0;
    d->state = d->PLAY;
    d->pc.r = 255;
    d->pc.g = 255;
    d->pc.b = 255;
    d->pc.life = 3;
    d->resultSize = 0;

}
void play(struct DATA* d) {
    if (!isTrigger(KEY_A) && !isTrigger(KEY_S) && !isTrigger(KEY_D) ){
        return;
    }
         //�v���C���[�̎�
    if (isTrigger(KEY_A)) { d->player.hand = d->GU; }
    if (isTrigger(KEY_S)) {d->player.hand = d->CHOKI;}
    if (isTrigger(KEY_D)) { d->player.hand = d->PA; }
    //�o�b�̎�
    d->pc.hand = random() % 3;
        //������������
        if (d->player.hand == d->pc.hand) {
            //������
            d->player.r = 255;d->player.g = 255;d->player.b = 255;
            d->pc.r = 255;d->pc.g = 255;d->pc.b = 255;
        }
        else if ((d->player.hand + 1)%3==d->pc.hand){
            //�v���C���[����
            d->pc.life--;
            d->player.r = 255;d->player.g = 200;d->player.b = 200;
            d->pc.r = 255;d->pc.g = 255;d->pc.b = 255;
        }
        else {
            //pc����
            d->player.life--;
            d->player.r = 255;d->player.g = 255;d->player.b = 255;
            d->pc.r = 255;d->pc.g = 200;d->pc.b = 200;
        }
        if (d->player.life == 0 || d->pc.life == 0) {
            d->state = d->RESULT;
        }
}
void result(struct DATA* d) {
    if (d->player.life == 0) {
        d->player.py += 1;
        d->player.angle += 0.003f;
    }
    else{
        d->pc.py += 1;
        d->pc.angle += -0.003f;
    }
    if (d->resultSize < 180) {
        d->resultSize += 10;
    }
    if (isTrigger(KEY_SPACE)) 
    { d->state = d->INIT; }
}
void draw(struct DATA* d) {
    clear(180);
    rectMode(CENTER);
    imageColor(d->player.r,d->player.g,d->player.b);
    image(d->player.img[d->player.hand], d->player.px,
        d->player.py, d->player.angle);
    imageColor(d->pc.r, d->pc.g, d->pc.b);
    image(d->pc.img[d->pc.hand], d->pc.px,
        d->pc.py, d->pc.angle);
    imageColor(255, 0, 0);
    for (int i = 0;i < d->player.life;i++) {
        image(d->heartImg, d->player.px+50*(i-1), d->player.py - 110);
    }
    imageColor(255, 0, 0);
    for (int i = 0;i < d->pc.life;i++) {
        image(d->heartImg, d->pc.px + 50 * (i - 1), d->pc.py - 110);
    }
    if (d->state == d->RESULT) {
        textSize(d->resultSize);
        if (d->player.life > 0) {
            fill(255, 0, 0);
            text("����",255, 320);
        }
        else {
            fill(0, 0, 200);
            text("����", 225, 320);
        }
    }
}

void gmain() {
    window(800, 450);
    struct DATA d;
    loadImages(&d);
    while (notQuit) {
        if      (d.state == d.INIT  ) { init(&d); }
        else if (d.state == d.PLAY  ) { play(&d); }
        else if (d.state == d.RESULT) { result(&d); }
        draw(&d);
    }
}

#else

#include"libOne.h"

struct HAND {
    int hand;
    int img[3];
    int heartImg;
    float px;
    float py;
    struct COLOR color;
    float angle;
    int life;
};

struct RESULT_TEXT {
    const char* str;
    float px;
    float py;
    float size;
    struct COLOR color;
};

struct DATA {
    int INIT = 0;
    int PLAY = 1;
    int RESULT = 2;
    int state = INIT;

    struct COLOR pink = { 255,200,200 };
    struct COLOR white = { 255,255,255 };
    struct COLOR red = { 255,0,0 };
    struct COLOR blue = { 0,0,200 };
    int GU = 0;
    int CHOKI = 1;
    int PA = 2;
    struct HAND player;
    struct HAND pc;
    struct RESULT_TEXT resultText;
};

void drawHands(struct DATA* d);
void drawResultText(struct DATA* d);

void loadImages(struct DATA* d) {
    d->player.img[d->GU] = loadImage("assets\\playerGu.png");
    d->player.img[d->CHOKI] = loadImage("assets\\playerChoki.png");
    d->player.img[d->PA] = loadImage("assets\\playerPa.png");
    d->player.heartImg = loadImage("assets\\heart.png");
    d->pc.img[d->GU] = loadImage("assets\\pcGu.png");
    d->pc.img[d->CHOKI] = loadImage("assets\\pcChoki.png");
    d->pc.img[d->PA] = loadImage("assets\\pcPa.png");
    d->pc.heartImg = d->player.heartImg;
}
void init(struct DATA* d) {
    d->player.hand = d->GU;
    d->player.px = 250;
    d->player.py = 225;
    d->player.color = d->white;
    d->player.life = 3;
    d->player.angle = 0;

    d->pc.hand = d->GU;
    d->pc.px = 550;
    d->pc.py = 225;
    d->pc.color = d->white;
    d->pc.life = 3;
    d->pc.angle = 0;

    d->resultText.str = "����";
    d->resultText.color = d->red;
    d->resultText.px = 255;
    d->resultText.py = 320;
    d->resultText.size = 0;
    
    drawHands(d);

    //�X�e�[�g�؂�ւ�
    d->state = d->PLAY;
}
void play(struct DATA* d) {
    if (!isTrigger(KEY_A) && !isTrigger(KEY_S) && !isTrigger(KEY_D)) {
        return;
    }
    //�v���C���[�̎�
    if (isTrigger(KEY_A)) { d->player.hand = d->GU; }
    if (isTrigger(KEY_S)) { d->player.hand = d->CHOKI; }
    if (isTrigger(KEY_D)) { d->player.hand = d->PA; }
    //�o�b�̎�
    d->pc.hand = random() % 3;
    //���ʔ���
    if (d->player.hand == d->pc.hand) {
        //������
        d->player.color = d->white;
        d->pc.color = d->white;
    }
    else if ((d->player.hand + 1) % 3 == d->pc.hand) {
        //�v���C���[����
        d->pc.life--;
        d->player.color = d->pink;
        d->pc.color = d->white;
    }
    else {
        //�o�b����
        d->player.life--;
        d->player.color = d->white;
        d->pc.color = d->pink;
    }
    //�`��
    drawHands(d);
    //�X�e�[�g�؂�ւ�
    if (d->player.life == 0 || d->pc.life == 0) {
        if (d->player.life == 0) {
            d->resultText.str = "����";
            d->resultText.color = d->blue;
        }
        d->state = d->RESULT;
    }
}
void result(struct DATA* d) {
    //�������肪��]���Ȃ��痎���Ă���
    if (d->player.life == 0) {
        d->player.py += 1;
        d->player.angle += 0.003f;
    }
    else {
        d->pc.py += 1;
        d->pc.angle += -0.003f;
    }
    //���ʕ����g��
    if (d->resultText.size < 180) {
        d->resultText.size += 10;
    }
    //�`��
    drawHands(d);
    drawResultText(d);
    //�X�e�[�g�؂�ւ�
    if (isTrigger(KEY_SPACE)) {
        d->state = d->INIT;
    }
}

void drawHand(struct HAND* hand) {
    //��
    rectMode(CENTER);
    imageColor(hand->color);
    int i = hand->hand;
    image(hand->img[i], hand->px, hand->py, hand->angle);
    //�n�[�g
    imageColor(255, 0, 0);
    for (i = 0; i < hand->life; i++) {
        image(hand->heartImg, hand->px + 50 * (i - 1), hand->py - 100);
    }
}
void drawHands(struct DATA* d) {
    clear(180);
    drawHand(&d->player);
    drawHand(&d->pc);
}
void drawResultText(struct DATA* d) {
    textSize(d->resultText.size);
    fill(d->resultText.color);
    text(d->resultText.str, d->resultText.px, d->resultText.py);
}

void gmain() {
    //�E�B���h�E�\��
    window(800, 450);
    //�f�[�^�p��
    struct DATA d;
    //�摜�ǂݍ���
    loadImages(&d);
    //���C�����[�v
    while (notQuit) {
        //�X�e�[�g����
        if      (d.state == d.INIT  ) { init(&d); }
        else if (d.state == d.PLAY  ) { play(&d); }
        else if (d.state == d.RESULT) { result(&d); }
    }
}
#endif
