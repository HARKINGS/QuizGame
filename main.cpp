#include <bits/stdc++.h>
#include <Engine.h>

using namespace std;

int tt = 0, cnt = 0, Score = 0;
char Answer[41], ChooseAns[41], AnsF[41];
time_t Now = time('\0');

void guildText(void)
{

}

int main(int argc, char** argv)
{
    for(int i = 1; i <= 40; ++i)
    {
        Answer[i] = '1';
        ChooseAns[i] = ' ';
        AnsF[i] = ' ';
    }

    Engine::GetInstance()->Init();

    while(Engine::GetInstance()->IsRunning())
    {
        Engine::GetInstance()->Events();
        Engine::GetInstance()->Update(tt);

        if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_KP_ENTER))
            cnt = NumQuestion + 1;

        if(!tt)
        {
            Engine::GetInstance()->Render();
            if(Engine::GetInstance()->Start()) tt++;
        }
        else if(cnt <= NumQuestion)
        {
            /// thoi gian
            time_t now = time('\0');

            if(now - Now == 2400)
            {
                cnt = NumQuestion + 1;
                continue;
            }

            Engine::GetInstance()->RenderPlay(tt, now - Now);

            /// chon cau hoi
            int id = Input::GetInstance()->GetId();
            if(id)
            {
                Engine::GetInstance()->Reset();
                tt = id;
                continue;
            }

            /// nop bai
            std::pair <int, int> m_Direction;
            m_Direction = Input::GetInstance()->GetDir();

            if(m_Direction.first >= SCREEN_WIDTH - 450 && m_Direction.second >= SCREEN_HEIGHT - 150 &&
                m_Direction.first <= SCREEN_WIDTH && m_Direction.second <= SCREEN_HEIGHT)
                    cnt = NumQuestion + 1;

            /// tra loi chuyen cau
            char Ans = Engine::GetInstance()->Choose();
            bool check = RandNum::GetInstance()->GetAnswer(tt);
            if(Ans != ' ')
            {
                char Type = Engine::GetInstance()->GetAns();

                if(Type != ' ')
                {
                    ///* xet cau tra loi *///
                    if(Ans == Answer[tt]) /// dung
                    {
                        if(ChooseAns[tt] != Ans)
                            Score++;
                    }
                    else /// sai
                    {
                        if(ChooseAns[tt] == Answer[tt])
                            Score--;
                    }

                    ChooseAns[tt] = Ans;

                    ///* xet chuyen cau *///
                    if(Type == 'U')
                    {
                        cout << "cau " << tt << ": " << Ans << '\n';
                        cnt += (check == false);
                        RandNum::GetInstance()->Active(tt);
                        tt = tt % NumQuestion + 1;
                    }
                    else if(Type == 'D')
                    {
                        cout << "cau " << tt << ": " << Ans << '\n';
                        cnt += (check == false);
                        RandNum::GetInstance()->Active(tt);
                        if(tt == 1) tt = NumQuestion;
                        else tt = tt - 1;
                    }
                }
            }
        }
        else if(cnt > NumQuestion)
        {
            Engine::GetInstance()->RenderEnd(Score);
            if(Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
                Engine::GetInstance()->Quit();
        }
    }

    Engine::GetInstance()->Clean();

    return 0;
}
