FROM python:alpine

RUN pip install --upgrade pip
RUN pip install cpplint

ENTRYPOINT sh -c "cpplint --recursive */*"