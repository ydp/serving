import tensorflow as tf
from tensorflow_serving.apis import classification_pb2
from tensorflow_serving.apis import inference_pb2
from tensorflow_serving.apis import model_pb2
from tensorflow_serving.apis import predict_pb2
from tensorflow_serving.apis import prediction_log_pb2
from tensorflow_serving.apis import regression_pb2

def main():
    with tf.python_io.TFRecordWriter("tf_serving_warmup_requests") as writer:
        # replace <request> with one of:
        # predict_pb2.PredictRequest(..)
        # classification_pb2.ClassificationRequest(..)
        # regression_pb2.RegressionRequest(..)
        # inference_pb2.MultiInferenceRequest(..)
        request = predict_pb2.PredictRequest()
        request.model_spec.name = 'tensorflow'
        request.model_spec.signature_name = 'serving_default'
        request.inputs['inputs'].CopyFrom(
            tf.contrib.util.make_tensor_proto(features, shape=[batch_size]))
        log = prediction_log_pb2.PredictionLog(
            predict_log=prediction_log_pb2.PredictLog(request=request))
        writer.write(log.SerializeToString())

if __name__ == "__main__":
    main()
