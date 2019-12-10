FROM python:alpine

LABEL "com.github.actions.name"="CppLinter"
LABEL "com.github.actions.description"="Run CppLint on your files!"
LABEL "com.github.actions.icon"="upload-cloud"
LABEL "com.github.actions.color"="6f42c1"

RUN pip install --upgrade pip
RUN pip install cpplint

CMD ["cpplint", "/github/workspace/*/*"]