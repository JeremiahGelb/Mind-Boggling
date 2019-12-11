FROM python:alpine

RUN pip install --upgrade pip
RUN pip install cpplint

ENTRYPOINT ["cpplint", "src/*"]