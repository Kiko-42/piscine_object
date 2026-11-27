#ifndef TOOL_HPP
#define TOOL_HPP

class Tool
{
public:
    Tool();
    virtual ~Tool();
    virtual void use() = 0; //TODO: あれ、なんで0を入れるんだっけ。virtualだけだとTool.useもcallしちゃうからか。そこで定義がないままだとコンパイラに怒られそうだし、明示的に0をいれているんだっけ。あれ、なんで0を入れるんだっけ。関数ってアドレスを指しているはずだから、0を指すと0x00を指すよね。いいの？そこになにか入っている可能性は？スタック領域の0x00ってなにか特別なんだっけ？

};

#endif
