#ifndef __M5LiteTouch_H__
#define __M5LiteTouch_H__

typedef struct point
{
  int x;
  int y;
} TouchPoint_t;

class M5LiteTouch {
  public:
    void setLcd(TFT_eSPI *Lcd) {
      _Lcd = Lcd;
    }

    bool ispressed() {
      return (_TouchPoint.x != -1);
    }

    TouchPoint_t getPressPoint() {
      return _TouchPoint;
    }

    void update() {
      if (enable) {
        if (!_Lcd->getTouchRaw(&_TouchPoint.x, &_TouchPoint.y)) {
          _TouchPoint.x = -1;
          _TouchPoint.y = -1;
        }
      }
    }

    bool enable = false;

  private:
    TouchPoint_t _TouchPoint = { -1, -1};
    TFT_eSPI *_Lcd;
};

#endif
