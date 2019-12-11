FROM python:alpine

RUN pip install --upgrade pip
RUN pip install cpplint

COPY entrypoint.sh /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]