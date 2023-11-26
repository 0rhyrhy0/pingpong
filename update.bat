@echo off

git add .
git commit -m "%*"
git push

: 모든 파일에 같은 커밋 메시지를 써도 될 때만 사용.
: 아닌 경우, 
: : git commit -m "commit message" (file)
: 을 사용하여 따로따로 메시지를 작성한 후 push함.

: 20231126 - GPG 설정을 완료하였음.