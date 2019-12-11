FROM python:alpine

RUN pip install --upgrade pip
RUN pip install cpplint

CMD sh -c "cpplint --recursive */*"